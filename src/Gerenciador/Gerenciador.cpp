// Includes necessários
#include "Gerenciador.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <limits>

#include "../SolucionadorEDS/SolucionadorEDS.h"
#include "../Grafo/Grafo.h"

// Implementação da geração automática de relatório EDS
void Gerenciador::gerarRelatorioAutomaticoEDS() {
    std::cout << "\n======================================================\n";
    std::cout << "INICIANDO GERACAO DO RELATORIO DE DESEMPENHO..." << std::endl;
    std::cout << "Isso pode levar alguns minutos...\n";
    std::cout << "======================================================\n\n";

    std::map<std::string, int> dynamic_best_solutions;

    std::vector<double> alpha_values = {0.2, 0.3, 0.4};
    const int num_executions = 10;
    const int num_randomized_calls = 30;
    const int num_reactive_calls = 300;
    int semente = 42; // Semente fixa para reprodutibilidade

    struct ExecutionResult {
        double solution_value;
        double execution_time;
    };

    std::map<std::string, std::vector<ExecutionResult>> greedy_results;
    std::map<std::string, std::map<double, std::vector<ExecutionResult>>> randomized_results;
    std::map<std::string, std::vector<ExecutionResult>> reactive_results;

    // Mapeamento dos nomes esperados para os arquivos reais
    std::vector<std::string> real_files = {
        "grafo-t2-1.txt", "grafo-t2-2.txt", "grafo-t2-3.txt", "grafo-t2-4.txt", "grafo-t2-5.txt", "grafo-t2-6.txt",
        "grafo-t2-7.txt", "grafo-t2-8.txt", "grafo-t2-9.txt", "grafo-t2-10.txt", "grafo-t2-11.txt", "grafo-t2-12.txt",
        "grafo-t2-13.txt", "grafo-t2-14.txt", "grafo-t2-15.txt", "grafo-t2-16.txt", "grafo-t2-17.txt", "grafo-t2-18.txt"
    };
    std::vector<std::string> expected_names = {
        "g_25_0.16_0_1_0", "g_25_0.16_0_1_1", "g_25_0.21_0_1_0", "g_25_0.21_0_1_1", "g_25_0.26_0_1_0", "g_25_0.26_0_1_1",
        "g_40_0.10_0_1_0", "g_40_0.10_0_1_1", "g_40_0.15_0_1_0", "g_40_0.15_0_1_1", "g_40_0.20_0_1_0", "g_40_0.20_0_1_0_2",
        "g_60_0.07_0_1_0", "g_60_0.07_0_1_1", "g_60_0.12_0_1_0", "g_60_0.12_0_1_1", "g_60_0.17_0_1_0", "g_60_0.17_0_1_1"
    };
    std::map<std::string, std::string> instance_to_file;
    for (size_t i = 0; i < expected_names.size(); ++i) {
        instance_to_file[expected_names[i]] = real_files[i];
    }

    // Funções auxiliares
    auto mean = [](const std::vector<double>& v) {
        if (v.empty()) return 0.0;
        return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
    };
    auto best = [](const std::vector<double>& v) {
        if (v.empty()) return 0.0;
        return *std::min_element(v.begin(), v.end());
    };
    auto calculatePercentageDeviation = [](double result, double best_solution) {
        if (best_solution == 0) return 0.0;
        return (result - best_solution) / best_solution;
    };

    // Loop de experimentos
    for (const auto& instance : expected_names) {
        std::string path = "instancias_t2/" + instance_to_file.at(instance);
        Grafo* grafo = new Grafo(path.c_str());
        SolucionadorEDS solver(grafo);

        int current_instance_best = std::numeric_limits<int>::max();

        // Guloso padrão
        for (int i = 0; i < num_executions; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            auto sol = solver.executarGuloso();
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            greedy_results[instance].push_back({(double)sol.size(), duration.count()});
            current_instance_best = std::min(current_instance_best, (int)sol.size());
        }

        // Guloso randomizado para cada alfa
        for (double alpha : alpha_values) {
            for (int i = 0; i < num_executions; ++i) {
                auto start = std::chrono::high_resolution_clock::now();
                auto sol = solver.executarGRA(num_randomized_calls, semente + i, alpha);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;
                randomized_results[instance][alpha].push_back({(double)sol.size(), duration.count()});
                current_instance_best = std::min(current_instance_best, (int)sol.size());
            }
        }

        // Guloso randomizado reativo
        for (int i = 0; i < num_executions; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            auto sol = solver.executarGRAR(num_reactive_calls, semente + i);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            reactive_results[instance].push_back({(double)sol.size(), duration.count()});
            current_instance_best = std::min(current_instance_best, (int)sol.size());
        }
        
        dynamic_best_solutions[instance] = current_instance_best;
        std::cout << "Instancia " << instance << " processada. Melhor valor encontrado: " << current_instance_best << std::endl;

        delete grafo;
    }

    // Geração do relatório
    std::ofstream report_file("relatorio_resultados.txt");
    if (!report_file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de relatório." << std::endl;
        return;
    }
    report_file << std::fixed << std::setprecision(4);

    auto simplifica_nome = [](const std::string& nome) -> std::string {
        size_t p1 = nome.find('_');
        if (p1 == std::string::npos) return nome;
        size_t p2 = nome.find('_', p1+1);
        if (p2 == std::string::npos) return nome;
        size_t p3 = nome.find('_', p2+1);
        if (p3 == std::string::npos) return nome;
        std::string nvert = nome.substr(p1+1, p2-p1-1);
        std::string dens = nome.substr(p2+1, p3-p2-1);
        return nvert + "v_" + dens;
    };

    // Tabela 1: Resultados (melhor e média)
    report_file << "==============================\n";
    report_file << "TABELA 1: RESULTADOS (MELHOR E MÉDIA)\n";
    report_file << "------------------------------\n";
    report_file << std::left << std::setw(12) << "Instância" << std::setw(8) << "Best" << std::setw(16) << "Guloso(Melhor)" << std::setw(16) << "Guloso(Média)";
    for (double alpha : alpha_values) {
        report_file << std::setw(18) << ("Rand(" + std::to_string(alpha) + ")Melhor") << std::setw(18) << ("Rand(" + std::to_string(alpha) + ")Média");
    }
    report_file << std::setw(16) << "Reativo(Melhor)" << std::setw(16) << "Reativo(Média)" << "\n";
    report_file << std::string(110, '-') << "\n";
    
    for (const auto& pair : dynamic_best_solutions) {
        std::string instance = pair.first;
        double best_val = static_cast<double>(pair.second);
        std::string nome_simples = simplifica_nome(instance);
        std::vector<double> greedy_solutions;
        for (const auto& r : greedy_results.at(instance)) greedy_solutions.push_back(r.solution_value);
        double best_greedy = best(greedy_solutions);
        double avg_greedy = mean(greedy_solutions);
        report_file << std::left << std::setw(12) << nome_simples << std::setw(8) << best_val << std::setw(16) << best_greedy << std::setw(16) << avg_greedy;
        for (double alpha : alpha_values) {
            std::vector<double> rand_solutions;
            for (const auto& r : randomized_results.at(instance).at(alpha)) rand_solutions.push_back(r.solution_value);
            double best_rand = best(rand_solutions);
            double avg_rand = mean(rand_solutions);
            report_file << std::setw(18) << best_rand << std::setw(18) << avg_rand;
        }
        std::vector<double> reactive_solutions;
        for (const auto& r : reactive_results.at(instance)) reactive_solutions.push_back(r.solution_value);
        double best_reactive = best(reactive_solutions);
        double avg_reactive = mean(reactive_solutions);
        report_file << std::setw(16) << best_reactive << std::setw(16) << avg_reactive << "\n";
    }

    // Tabela 2: Desvio percentual em relação ao best
    report_file << "\n==============================\n";
    report_file << "TABELA 2: DESVIO PERCENTUAL EM RELAÇÃO AO BEST\n";
    report_file << "------------------------------\n";
    report_file << std::left << std::setw(12) << "Instância" << std::setw(16) << "Guloso";
    for (double alpha : alpha_values) report_file << std::setw(18) << ("Rand(" + std::to_string(alpha) + ")");
    report_file << std::setw(16) << "Reativo" << "\n";
    report_file << std::string(70, '-') << "\n";

    for (const auto& pair : dynamic_best_solutions) {
        std::string instance = pair.first;
        double best_val = static_cast<double>(pair.second);
        std::string nome_simples = simplifica_nome(instance);
        std::vector<double> greedy_solutions;
        for (const auto& r : greedy_results.at(instance)) greedy_solutions.push_back(r.solution_value);
        double avg_greedy = best(greedy_solutions);
        double dev_greedy = calculatePercentageDeviation(avg_greedy, best_val);
        report_file << std::left << std::setw(12) << nome_simples << std::setw(16) << dev_greedy;
        for (double alpha : alpha_values) {
            std::vector<double> rand_solutions;
            for (const auto& r : randomized_results.at(instance).at(alpha)) rand_solutions.push_back(r.solution_value);
            double avg_rand = best(rand_solutions);
            double dev_rand = calculatePercentageDeviation(avg_rand, best_val);
            report_file << std::setw(18) << dev_rand;
        }
        std::vector<double> reactive_solutions;
        for (const auto& r : reactive_results.at(instance)) reactive_solutions.push_back(r.solution_value);
        double avg_reactive = best(reactive_solutions);
        double dev_reactive = calculatePercentageDeviation(avg_reactive, best_val);
        report_file << std::setw(16) << dev_reactive << "\n";
    }

    // Tabela 3: Tempos médios de processamento
    report_file << "\n==============================\n";
    report_file << "TABELA 3: TEMPOS MÉDIOS DE PROCESSAMENTO (SEGUNDOS)\n";
    report_file << "------------------------------\n";
    report_file << std::left << std::setw(12) << "Instância" << std::setw(16) << "Guloso";
    for (double alpha : alpha_values) report_file << std::setw(18) << ("Rand(" + std::to_string(alpha) + ")");
    report_file << std::setw(16) << "Reativo" << "\n";
    report_file << std::string(70, '-') << "\n";
    
    for (const auto& pair : dynamic_best_solutions) {
        std::string instance = pair.first;
        std::string nome_simples = simplifica_nome(instance);
        std::vector<double> greedy_times;
        for (const auto& r : greedy_results.at(instance)) greedy_times.push_back(r.execution_time);
        double avg_greedy_time = mean(greedy_times);
        report_file << std::left << std::setw(12) << nome_simples << std::setw(16) << avg_greedy_time;
        for (double alpha : alpha_values) {
            std::vector<double> rand_times;
            for (const auto& r : randomized_results.at(instance).at(alpha)) rand_times.push_back(r.execution_time);
            double avg_rand_time = mean(rand_times);
            report_file << std::setw(18) << avg_rand_time;
        }
        std::vector<double> reactive_times;
        for (const auto& r : reactive_results.at(instance)) reactive_times.push_back(r.execution_time);
        double avg_reactive_time = mean(reactive_times);
        report_file << std::setw(16) << avg_reactive_time << "\n";
    }

    report_file.close();
    std::cout << "\nRelatorio gerado em 'relatorio_resultados.txt'\n";
}

// Menu de comandos
void Gerenciador::comandos(Grafo* grafo) {
    while (true) {
        cout << endl << "--------------------------------------------------------------------------------------------------" << endl;
        cout << "Digite uma das opcoes abaixo e pressione enter:" << endl << endl;
        cout << "(a) Fecho transitivo direto de um no;" << endl;
        cout << "(b) Fecho transitivo indireto de um no;" << endl;
        cout << "(c) Caminho minimo (Dijkstra);" << endl;
        cout << "(d) Caminho minimo (Floyd);" << endl;
        cout << "(e) Arvore Geradora Minima (Algoritmo de Prim);" << endl;
        cout << "(f) Arvore Geradora Minima (Algoritmo de Kruskal);" << endl;
        cout << "(g) Arvore de caminhamento em profundidade;" << endl;
        cout << "(h) Raio, diametro, centro e periferia do grafo;" << endl;
        cout << "(i) Edge Dominating Set (Algoritmo Guloso);" << endl;
    cout << "(r) Gerar relatório de resultados;" << endl;
    cout << "(0) Sair;" << endl << endl;

        char resp;
        cin >> resp;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        switch (tolower(resp)) {
            case 'r': {
                // Chama a função de relatório automático
                gerarRelatorioAutomaticoEDS();
                break;
            }
            case 'a': {
                if (!grafo->in_direcionado) {
                    cout << "ERRO: Esta funcionalidade e valida apenas para grafos direcionados." << endl;
                    break;
                }
                char id_no = get_id_entrada();
                vector<char> fecho = grafo->fecho_transitivo_direto(id_no);
                cout << "Fecho transitivo direto de " << id_no << ": ";
                imprimir_vector_char(fecho);

                if (pergunta_imprimir_arquivo("fecho_trans_dir.txt")) {
                    ofstream outfile("fecho_trans_dir.txt");
                    if (outfile.is_open()) {
                        for (size_t i = 0; i < fecho.size(); ++i) {
                            outfile << fecho[i] << (i < fecho.size() - 1 ? "," : "");
                        }
                        outfile << endl;
                        outfile.close();
                        cout << "Saida salva em fecho_trans_dir.txt" << endl;
                    } else {
                        cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                    }
                }
                break;
            }
            case 'i': {
                // Edge Dominating Set - escolha do método
                cout << "Escolha o método para resolver o Conjunto Dominante de Arestas:" << endl;
                cout << "(1) Guloso" << endl;
                cout << "(2) Guloso Randomizado Adaptativo (GRA)" << endl;
                cout << "(3) Guloso Randomizado Adaptativo Reativo (GRAR)" << endl;
                int metodo = 0;
                cin >> metodo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                SolucionadorEDS solucionador(grafo);
                std::vector<std::pair<char, char>> sol;
                string nome_arquivo;
                double tempo = 0.0;
                if (metodo == 1) {
                    auto start = std::chrono::high_resolution_clock::now();
                    sol = solucionador.executarGuloso();
                    auto end = std::chrono::high_resolution_clock::now();
                    tempo = std::chrono::duration<double>(end - start).count();
                    nome_arquivo = "eds_guloso.txt";
                    cout << "Conjunto Dominante de Arestas (Guloso):" << endl;
                } else if (metodo == 2) {
                    int iter, seed;
                    double alpha;
                    cout << "Digite o número de iterações: ";
                    cin >> iter;
                    cout << "Digite a semente de randomização: ";
                    cin >> seed;
                    cout << "Digite o valor de alpha (ex: 0.3): ";
                    cin >> alpha;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    auto start = std::chrono::high_resolution_clock::now();
                    sol = solucionador.executarGRA(iter, seed, alpha);
                    auto end = std::chrono::high_resolution_clock::now();
                    tempo = std::chrono::duration<double>(end - start).count();
                    nome_arquivo = "eds_gra.txt";
                    cout << "Conjunto Dominante de Arestas (GRA):" << endl;
                } else if (metodo == 3) {
                    int iter, seed;
                    cout << "Digite o número de iterações: ";
                    cin >> iter;
                    cout << "Digite a semente de randomização: ";
                    cin >> seed;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    auto start = std::chrono::high_resolution_clock::now();
                    sol = solucionador.executarGRAR(iter, seed);
                    auto end = std::chrono::high_resolution_clock::now();
                    tempo = std::chrono::duration<double>(end - start).count();
                    nome_arquivo = "eds_grar.txt";
                    cout << "Conjunto Dominante de Arestas (GRAR):" << endl;
                } else {
                    cout << "Método inválido." << endl;
                    break;
                }
                if (sol.empty()) {
                    cout << "Nenhuma aresta selecionada." << endl;
                } else {
                    for (const auto& aresta : sol) {
                        cout << aresta.first << "-" << aresta.second << " ";
                    }
                    cout << endl;
                    cout << "Qualidade da solução (tamanho do conjunto): " << sol.size() << endl;
                    cout << "Tempo de execução (segundos): " << tempo << endl;
                }
                if (pergunta_imprimir_arquivo(nome_arquivo)) {
                    ofstream outfile(nome_arquivo);
                    if (outfile.is_open()) {
                        for (size_t i = 0; i < sol.size(); ++i) {
                            outfile << sol[i].first << "-" << sol[i].second;
                            if (i < sol.size() - 1) outfile << ",";
                        }
                        outfile << endl;
                        outfile.close();
                        cout << "Saida salva em " << nome_arquivo << endl;
                    } else {
                        cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                    }
                }
                break;
            }
            // ...existing code...
            case 'b': {
                if (!grafo->in_direcionado) {
                    cout << "ERRO: Esta funcionalidade e valida apenas para grafos direcionados." << endl;
                    break;
                }
                char id_no = get_id_entrada();
                vector<char> fecho = grafo->fecho_transitivo_indireto(id_no);
                cout << "Fecho transitivo indireto de " << id_no << ": ";
                imprimir_vector_char(fecho);

                if (pergunta_imprimir_arquivo("fecho_trans_indir.txt")) {
                    ofstream outfile("fecho_trans_indir.txt");
                    if (outfile.is_open()) {
                        for (size_t i = 0; i < fecho.size(); ++i) {
                            outfile << fecho[i] << (i < fecho.size() - 1 ? "," : "");
                        }
                        outfile << endl;
                        outfile.close();
                        cout << "Saida salva em fecho_trans_indir.txt" << endl;
                    } else {
                        cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                    }
                }
                break;
            }

            case 'c': {
                if (!grafo->in_ponderado_aresta) {
                    cout << "ERRO: O algoritmo de Dijkstra requer um grafo ponderado nas arestas." << endl;
                    break;
                }
                char id_no_1 = get_id_entrada();
                char id_no_2 = get_id_entrada();
                if (grafo->getNo(id_no_1) == nullptr || grafo->getNo(id_no_2) == nullptr) {
                    cout << "ERRO: Um ou ambos os vertices nao existem no grafo." << endl;
                    break;
                }
                vector<char> caminho = grafo->caminho_minimo_dijkstra(id_no_1, id_no_2);
                cout << "Caminho minimo de " << id_no_1 << " para " << id_no_2 << " (Dijkstra): ";
                imprimir_vector_char(caminho);

                if (pergunta_imprimir_arquivo("caminho_minimo_dijkstra.txt")) {
                    ofstream outfile("caminho_minimo_dijkstra.txt");
                    if (outfile.is_open()) {
                        for (size_t i = 0; i < caminho.size(); ++i) {
                            outfile << caminho[i] << (i < caminho.size() - 1 ? "," : "");
                        }
                        outfile << endl;
                        outfile.close();
                        cout << "Saida salva em caminho_minimo_dijkstra.txt" << endl;
                    } else {
                        cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                    }
                }
                break;
            }

            case 'd': {
                if (!grafo->in_ponderado_aresta) {
                    cout << "ERRO: O algoritmo de Floyd requer um grafo ponderado nas arestas." << endl;
                    break;
                }
                char id_no_1 = get_id_entrada();
                char id_no_2 = get_id_entrada();
                if (grafo->getNo(id_no_1) == nullptr || grafo->getNo(id_no_2) == nullptr) {
                    cout << "ERRO: Um ou ambos os vertices nao existem no grafo." << endl;
                    break;
                }
                vector<char> caminho = grafo->caminho_minimo_floyd(id_no_1, id_no_2);
                cout << "Caminho minimo de " << id_no_1 << " para " << id_no_2 << " (Floyd): ";
                imprimir_vector_char(caminho);

                if (pergunta_imprimir_arquivo("caminho_minimo_floyd.txt")) {
                    ofstream outfile("caminho_minimo_floyd.txt");
                    if (outfile.is_open()) {
                        for (size_t i = 0; i < caminho.size(); ++i) {
                            outfile << caminho[i] << (i < caminho.size() - 1 ? "," : "");
                        }
                        outfile << endl;
                        outfile.close();
                        cout << "Saida salva em caminho_minimo_floyd.txt" << endl;
                    } else {
                        cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                    }
                }
                break;
            }

            case 'e': {
                if (grafo->in_direcionado) {
                    cout << "ERRO: O algoritmo de Prim e aplicavel apenas a grafos nao direcionados." << endl;
                    break;
                }
                if (!grafo->in_ponderado_aresta) {
                    cout << "ERRO: O algoritmo de Prim requer um grafo ponderado nas arestas." << endl;
                    break;
                }
                if (!grafo->ehConexo()) { // Verificação restaurada
                    cout << "ERRO: O grafo nao e conexo, nao e possivel gerar uma AGM." << endl;
                    break;
                }
                
                int tam;
                string mensagem = "Digite o tamanho do subconjunto (entre 2 e " + to_string(grafo->ordem) + "): ";
                tam = solicitarInteiro(mensagem, grafo->ordem);

                if (tam > 0 && tam <= grafo->ordem) {
                    vector<char> ids = get_conjunto_ids(grafo, tam);
                    Grafo* agm = grafo->arvore_geradora_minima_prim(ids);
                    cout << "Arvore Geradora Minima (Prim):" << endl;
                    imprimir_grafo(agm);

                    if (pergunta_imprimir_arquivo("agm_prim.txt")) {
                        ofstream outfile("agm_prim.txt");
                        if (outfile.is_open()) {
                            // Lógica de salvar o grafo no arquivo
                            for (No* no : agm->lista_adj) {
                                outfile << no->id << ":";
                                if (!no->arestas.empty()) {
                                    for (size_t i = 0; i < no->arestas.size(); ++i) {
                                        outfile << " " << no->arestas[i]->id_no_alvo;
                                        if (agm->in_ponderado_aresta) outfile << "(" << no->arestas[i]->peso << ")";
                                        if (i < no->arestas.size() - 1) outfile << " ->";
                                    }
                                }
                                outfile << endl;
                            }
                            outfile.close();
                            cout << "Saida salva em agm_prim.txt" << endl;
                        } else {
                            cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                        }
                    }
                    delete agm;
                } else {
                    cout << "Valor invalido para o tamanho do subconjunto." << endl;
                }
                break;
            }

            case 'f': {
                if (grafo->in_direcionado) {
                    cout << "ERRO: O algoritmo de Kruskal e aplicavel apenas a grafos nao direcionados." << endl;
                    break;
                }
                if (!grafo->in_ponderado_aresta) {
                    cout << "ERRO: O algoritmo de Kruskal requer um grafo ponderado nas arestas." << endl;
                    break;
                }
                if (!grafo->ehConexo()) { // Verificação restaurada
                    cout << "ERRO: O grafo nao e conexo, nao e possivel gerar uma AGM." << endl;
                    break;
                }
                
                int tam;
                string mensagem = "Digite o tamanho do subconjunto (entre 2 e " + to_string(grafo->ordem) + "): ";
                tam = solicitarInteiro(mensagem, grafo->ordem);
                
                if (tam > 0 && tam <= grafo->ordem) {
                    vector<char> ids = get_conjunto_ids(grafo, tam);
                    Grafo* agm = grafo->arvore_geradora_minima_kruskal(ids);
                    cout << "Arvore Geradora Minima (Kruskal):" << endl;
                    imprimir_grafo(agm);

                     if (pergunta_imprimir_arquivo("agm_kruskal.txt")) {
                        ofstream outfile("agm_kruskal.txt");
                        if (outfile.is_open()) {
                            for (No* no : agm->lista_adj) {
                                outfile << no->id << ":";
                                if (!no->arestas.empty()) {
                                    for (size_t i = 0; i < no->arestas.size(); ++i) {
                                        outfile << " " << no->arestas[i]->id_no_alvo;
                                        if (agm->in_ponderado_aresta) outfile << "(" << no->arestas[i]->peso << ")";
                                        if (i < no->arestas.size() - 1) outfile << " ->";
                                    }
                                }
                                outfile << endl;
                            }
                            outfile.close();
                            cout << "Saida salva em agm_kruskal.txt" << endl;
                        } else {
                            cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                        }
                    }
                    delete agm;
                } else {
                    cout << "Valor invalido para o tamanho do subconjunto." << endl;
                }
                break;
            }

            case 'g': {
                char id_no = get_id_entrada();
                if (grafo->getNo(id_no) == nullptr) {
                    cout << "ERRO: O vertice nao existe no grafo." << endl;
                    break;
                }
                Grafo* arvore = grafo->arvore_caminhamento_profundidade(id_no);
                cout << "Arvore de caminhamento em profundidade a partir de " << id_no << ":" << endl;
                imprimir_grafo(arvore);

                 if (pergunta_imprimir_arquivo("arvore_caminhamento_profundidade.txt")) {
                    ofstream outfile("arvore_caminhamento_profundidade.txt");
                    if (outfile.is_open()) {
                         for (No* no : arvore->lista_adj) {
                            outfile << no->id << ":";
                            if (!no->arestas.empty()) {
                                for (size_t i = 0; i < no->arestas.size(); ++i) {
                                    outfile << " " << no->arestas[i]->id_no_alvo;
                                    if (arvore->in_ponderado_aresta) outfile << "(" << no->arestas[i]->peso << ")";
                                    if (i < no->arestas.size() - 1) outfile << " ->";
                                }
                            }
                            outfile << endl;
                        }
                        outfile.close();
                        cout << "Saida salva em arvore_caminhamento_profundidade.txt" << endl;
                    } else {
                        cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                    }
                }
                delete arvore;
                break;
            }

            case 'h': {
                if (grafo->in_direcionado) {
                    cout << "ERRO: Raio, diametro, centro e periferia sao para grafos nao direcionados." << endl;
                    break;
                }
                if (!grafo->in_ponderado_aresta) {
                    cout << "AVISO: Este calculo e mais significativo para grafos ponderados nas arestas." << endl;
                }
                int r = grafo->raio();
                int d = grafo->diametro();
                vector<char> cent = grafo->centro();
                vector<char> perif = grafo->periferia();
                imprimir_h_output(r, d, cent, perif);

                if (pergunta_imprimir_arquivo("raio_diametro_centro_periferia.txt")) {
                    ofstream outfile("raio_diametro_centro_periferia.txt");
                    if (outfile.is_open()) {
                        outfile << r << endl;
                        outfile << d << endl;
                        for (size_t i = 0; i < cent.size(); ++i) {
                            outfile << cent[i] << (i < cent.size() - 1 ? "," : "");
                        }
                        outfile << endl;
                        for (size_t i = 0; i < perif.size(); ++i) {
                            outfile << perif[i] << (i < perif.size() - 1 ? "," : "");
                        }
                        outfile << endl;
                        outfile.close();
                        cout << "Saida salva em raio_diametro_centro_periferia.txt" << endl;
                    } else {
                        cout << "ERRO: Nao foi possivel criar o arquivo de saida." << endl;
                    }
                }
                break;
            }

            case '0': {
                cout << "Encerrando o programa." << endl;
                return; // MUDANÇA 3: 'return' encerra a função e, consequentemente, o laço while.
            }
            default: {
                cout << "Opcao invalida" << endl;
                break;
            }
        }
    }
}

char Gerenciador::get_id_entrada() {
    cout << "Digite o id de um no: ";
    char id;
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return id;
}

vector<char> Gerenciador::get_conjunto_ids(Grafo *grafo, int tam) {
    vector<char> ids = {};
    cout << "Digite " << tam << " IDs para o subconjunto:" << endl;
    while ((int)ids.size() < tam) {
        char id_no = get_id_entrada();
        bool existe = false;
        for (No* no : grafo->lista_adj) {
            if (no->id == id_no) {
                existe = true;
                break;
            }
        }

        if (!existe) {
            cout << "Vertice nao existe. Tente novamente." << endl;
        } else {
            bool repetido = find(ids.begin(), ids.end(), id_no) != ids.end();
            if (repetido) {
                cout << "Valor repetido. Tente novamente." << endl;
            } else {
                ids.push_back(id_no);
            }
        }
    }
    return ids;
}

bool Gerenciador::pergunta_imprimir_arquivo(string nome_arquivo) {
    cout << endl << "Imprimir em arquivo externo? (" << nome_arquivo << ")" << endl;
    cout << "(1) Sim;" << endl;
    cout << "(2) Nao." << endl;
    int resp;
    cin >> resp;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;

    switch (resp) {
        case 1:
            return true;
        case 2:
            return false;
        default:
            cout << "Resposta invalida. Por favor, digite 1 para Sim ou 2 para Nao." << endl;
            return pergunta_imprimir_arquivo(nome_arquivo);
    }
}

void Gerenciador::imprimir_vector_char(const vector<char>& vec) {
    if (vec.empty()) {
        cout << "Nenhum resultado." << endl;
        return;
    }
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << ",";
        }
    }
    cout << endl << endl;
}

void Gerenciador::imprimir_grafo(Grafo* grafo) {
    if (grafo == nullptr || grafo->lista_adj.empty()) {
        cout << "Grafo vazio ou nulo." << endl;
        return;
    }
    for (No* no : grafo->lista_adj) {
        cout << no->id << ":";
        if (!no->arestas.empty()) {
            for (size_t i = 0; i < no->arestas.size(); ++i) {
                cout << " " << no->arestas[i]->id_no_alvo;
                if (grafo->in_ponderado_aresta) {
                    cout << "(" << no->arestas[i]->peso << ")";
                }
                if (i < no->arestas.size() - 1) {
                    cout << " ->";
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Gerenciador::imprimir_h_output(int raio, int diametro, const vector<char>& centro, const vector<char>& periferia) { 
    cout << "Raio: " << raio << endl;
    cout << "Diametro: " << diametro << endl;
    cout << "Centro: ";
    if (centro.empty()) {
        cout << "Nenhum";
    } else {
        for (size_t i = 0; i < centro.size(); ++i) {
            cout << centro[i];
            if (i < centro.size() - 1) {
                cout << ",";
            }
        }
    }
    cout << endl;
    cout << "Periferia: ";
    if (periferia.empty()) {
        cout << "Nenhum";
    } else {
        for (size_t i = 0; i < periferia.size(); ++i) {
            cout << periferia[i];
            if (i < periferia.size() - 1) {
                cout << ",";
            }
        }
    }
    cout << endl << endl;
}

int Gerenciador::solicitarInteiro(string mensagem, int ordem) {
    int valor_validado;
    string input_str;
    int min_val = 2;

    while (true) {
        cout << mensagem;
        getline(cin, input_str);

        try {
            valor_validado = stoi(input_str);

            if (valor_validado >= min_val && valor_validado <= ordem) {
                return valor_validado;
            } else {
                cout << "Valor fora do intervalo. Digite um numero entre "
                     << min_val << " e " << ordem << "." << endl;
            }
        }
        catch (invalid_argument&) {
            cout << "Entrada invalida. Digite um numero inteiro." << endl;
        }
        catch (out_of_range&) {
            cout << "Numero muito grande ou muito pequeno. Tente novamente." << endl;
        }
    }
}