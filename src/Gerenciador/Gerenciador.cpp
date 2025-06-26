#include "Gerenciador.h"
#include <fstream>
#include <limits> // Para numeric_limits

void Gerenciador::comandos(Grafo* grafo) {
    // Limpa o buffer de entrada para evitar problemas com leituras anteriores
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
    cout << "(0) Sair;" << endl << endl;

    char resp;
    cin >> resp;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer após a leitura do char

    cout << endl; // Adiciona uma quebra de linha para melhor formatação

    switch (resp) {
        case 'a': {
            if (!grafo->in_direcionado) {
                cout << "ERRO: Esta funcionalidade e valida apenas para grafos direcionados." << endl;
                break;
            }
            char id_no = get_id_entrada();
            vector<char> fecho_transitivo_direto = grafo->fecho_transitivo_direto(id_no);
            cout << "Fecho transitivo direto de " << id_no << ": ";
            imprimir_vector_char(fecho_transitivo_direto);

            if (pergunta_imprimir_arquivo("fecho_trans_dir.txt")) {
                ofstream outfile("fecho_trans_dir.txt");
                if (outfile.is_open()) {
                    for (size_t i = 0; i < fecho_transitivo_direto.size(); ++i) {
                        outfile << fecho_transitivo_direto[i];
                        if (i < fecho_transitivo_direto.size() - 1) {
                            outfile << ",";
                        }
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

        case 'b': {
            if (!grafo->in_direcionado) {
                cout << "ERRO: Esta funcionalidade e valida apenas para grafos direcionados." << endl;
                break;
            }
            char id_no = get_id_entrada();
            vector<char> fecho_transitivo_indireto = grafo->fecho_transitivo_indireto(id_no);
            cout << "Fecho transitivo indireto de " << id_no << ": ";
            imprimir_vector_char(fecho_transitivo_indireto);

            if (pergunta_imprimir_arquivo("fecho_trans_indir.txt")) {
                ofstream outfile("fecho_trans_indir.txt");
                if (outfile.is_open()) {
                    for (size_t i = 0; i < fecho_transitivo_indireto.size(); ++i) {
                        outfile << fecho_transitivo_indireto[i];
                        if (i < fecho_transitivo_indireto.size() - 1) {
                            outfile << ",";
                        }
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
            vector<char> caminho_minimo_dijkstra = grafo->caminho_minimo_dijkstra(id_no_1, id_no_2);
            cout << "Caminho minimo de " << id_no_1 << " para " << id_no_2 << " (Dijkstra): ";
            imprimir_vector_char(caminho_minimo_dijkstra);

            if (pergunta_imprimir_arquivo("caminho_minimo_dijkstra.txt")) {
                ofstream outfile("caminho_minimo_dijkstra.txt");
                if (outfile.is_open()) {
                    for (size_t i = 0; i < caminho_minimo_dijkstra.size(); ++i) {
                        outfile << caminho_minimo_dijkstra[i];
                        if (i < caminho_minimo_dijkstra.size() - 1) {
                            outfile << ",";
                        }
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
            vector<char> caminho_minimo_floyd = grafo->caminho_minimo_floyd(id_no_1, id_no_2);
            cout << "Caminho minimo de " << id_no_1 << " para " << id_no_2 << " (Floyd): ";
            imprimir_vector_char(caminho_minimo_floyd);

            if (pergunta_imprimir_arquivo("caminho_minimo_floyd.txt")) {
                ofstream outfile("caminho_minimo_floyd.txt");
                if (outfile.is_open()) {
                    for (size_t i = 0; i < caminho_minimo_floyd.size(); ++i) {
                        outfile << caminho_minimo_floyd[i];
                        if (i < caminho_minimo_floyd.size() - 1) {
                            outfile << ",";
                        }
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
            // Verificar se o grafo é conexo antes de Prim 
            if (!grafo->ehConexo()) {
                cout << "ERRO: O grafo nao e conexo, nao e possivel gerar uma AGM." << endl;
                break;
            }

            int tam;
            cout << "Digite o tamanho do subconjunto (max " << grafo->ordem << "): ";
            cin >> tam;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (tam > 0 && tam <= grafo->ordem) {
                vector<char> ids = get_conjunto_ids(grafo, tam);
                Grafo* arvore_geradora_minima_prim = grafo->arvore_geradora_minima_prim(ids);
                cout << "Arvore Geradora Minima (Prim):" << endl;
                imprimir_grafo(arvore_geradora_minima_prim);

                if (pergunta_imprimir_arquivo("agm_prim.txt")) {
                    ofstream outfile("agm_prim.txt");
                    if (outfile.is_open()) {
                        for (No* no : arvore_geradora_minima_prim->lista_adj) {
                            outfile << no->id << ":";
                            if (!no->arestas.empty()) {
                                for (size_t i = 0; i < no->arestas.size(); ++i) {
                                    outfile << " " << no->arestas[i]->id_no_alvo;
                                    if (i < no->arestas.size() - 1) {
                                        outfile << " ->";
                                    }
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
                delete arvore_geradora_minima_prim;
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
            // Verificar se o grafo é conexo antes de Kruskal 
            if (!grafo->ehConexo()) {
                cout << "ERRO: O grafo nao e conexo, nao e possivel gerar uma AGM." << endl;
                break;
            }

            int tam;
            cout << "Digite o tamanho do subconjunto (max " << grafo->ordem << "): ";
            cin >> tam;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (tam > 0 && tam <= grafo->ordem) {
                vector<char> ids = get_conjunto_ids(grafo, tam);
                Grafo* arvore_geradora_minima_kruskal = grafo->arvore_geradora_minima_kruskal(ids);
                cout << "Arvore Geradora Minima (Kruskal):" << endl;
                imprimir_grafo(arvore_geradora_minima_kruskal);

                if (pergunta_imprimir_arquivo("agm_kruskal.txt")) {
                    ofstream outfile("agm_kruskal.txt");
                    if (outfile.is_open()) {
                        for (No* no : arvore_geradora_minima_kruskal->lista_adj) {
                            outfile << no->id << ":";
                            if (!no->arestas.empty()) {
                                for (size_t i = 0; i < no->arestas.size(); ++i) {
                                    outfile << " " << no->arestas[i]->id_no_alvo;
                                    if (i < no->arestas.size() - 1) {
                                        outfile << " ->";
                                    }
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
                delete arvore_geradora_minima_kruskal;
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
            Grafo* arvore_caminhamento_profundidade = grafo->arvore_caminhamento_profundidade(id_no);
            cout << "Arvore de caminhamento em profundidade a partir de " << id_no << ":" << endl;
            imprimir_grafo(arvore_caminhamento_profundidade);

            if (pergunta_imprimir_arquivo("arvore_caminhamento_profundidade.txt")) {
                ofstream outfile("arvore_caminhamento_profundidade.txt");
                if (outfile.is_open()) {
                    for (No* no : arvore_caminhamento_profundidade->lista_adj) {
                        outfile << no->id << ":";
                        if (!no->arestas.empty()) {
                            for (size_t i = 0; i < no->arestas.size(); ++i) {
                                outfile << " " << no->arestas[i]->id_no_alvo;
                                if (i < no->arestas.size() - 1) {
                                    outfile << " ->";
                                }
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
            delete arvore_caminhamento_profundidade;
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
                        outfile << cent[i];
                        if (i < cent.size() - 1) outfile << ",";
                    }
                    outfile << endl;
                    for (size_t i = 0; i < perif.size(); ++i) {
                        outfile << perif[i];
                        if (i < perif.size() - 1) outfile << ",";
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
            exit(0);
        }
        default: {
            cout << "Opcao invalida" << endl;
        }
    }

    comandos(grafo); // Repete o menu 
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
    cout << "Raio: " << raio << endl; // Valor do raio 
    cout << "Diametro: " << diametro << endl; // Valor do diametro 

    cout << "Centro: "; // vector<char> do centro 
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

    cout << "Periferia: "; // vector<char> da periferia 
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