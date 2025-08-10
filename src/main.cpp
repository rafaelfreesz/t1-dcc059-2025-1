
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <random>
#include <numeric>
#include <algorithm>
#include <map>
#include <iomanip>
#include "Grafo/Grafo.h"
#include "SolucionadorEDS/SolucionadorEDS.h"
#include "Gerenciador/Gerenciador.h"

struct ExecutionResult {
    double solution_value;
    double execution_time;
};

double mean(const std::vector<double>& v) {
    if (v.empty()) return 0.0;
    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}
double best(const std::vector<double>& v) {
    if (v.empty()) return 0.0;
    return *std::min_element(v.begin(), v.end());
}
double calculatePercentageDeviation(double result, double best_solution) {
    if (best_solution == 0) return 0.0;
    return (result - best_solution) / best_solution;
}

void generate_report(
    const std::string& filename,
    const std::map<std::string, int>& best_solutions,
    const std::vector<double>& alpha_values,
    const std::map<std::string, std::vector<ExecutionResult>>& greedy_results,
    const std::map<std::string, std::map<double, std::vector<ExecutionResult>>>& randomized_results,
    const std::map<std::string, std::vector<ExecutionResult>>& reactive_results
) {
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
    for (const auto& pair : best_solutions) {
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

    report_file << "\n==============================\n";
    report_file << "TABELA 2: DESVIO PERCENTUAL EM RELAÇÃO AO BEST\n";
    report_file << "------------------------------\n";
    report_file << std::left << std::setw(12) << "Instância" << std::setw(16) << "Guloso";
    for (double alpha : alpha_values) report_file << std::setw(18) << ("Rand(" + std::to_string(alpha) + ")");
    report_file << std::setw(16) << "Reativo" << "\n";
    report_file << std::string(70, '-') << "\n";
    for (const auto& pair : best_solutions) {
        std::string instance = pair.first;
        double best_val = static_cast<double>(pair.second);
        std::string nome_simples = simplifica_nome(instance);
        std::vector<double> greedy_solutions;
        for (const auto& r : greedy_results.at(instance)) greedy_solutions.push_back(r.solution_value);
        double avg_greedy = mean(greedy_solutions);
        double dev_greedy = calculatePercentageDeviation(avg_greedy, best_val);
        report_file << std::left << std::setw(12) << nome_simples << std::setw(16) << dev_greedy;
        for (double alpha : alpha_values) {
            std::vector<double> rand_solutions;
            for (const auto& r : randomized_results.at(instance).at(alpha)) rand_solutions.push_back(r.solution_value);
            double avg_rand = mean(rand_solutions);
            double dev_rand = calculatePercentageDeviation(avg_rand, best_val);
            report_file << std::setw(18) << dev_rand;
        }
        std::vector<double> reactive_solutions;
        for (const auto& r : reactive_results.at(instance)) reactive_solutions.push_back(r.solution_value);
        double avg_reactive = mean(reactive_solutions);
        double dev_reactive = calculatePercentageDeviation(avg_reactive, best_val);
        report_file << std::setw(16) << dev_reactive << "\n";
    }

    report_file << "\n==============================\n";
    report_file << "TABELA 3: TEMPOS MÉDIOS DE PROCESSAMENTO (SEGUNDOS)\n";
    report_file << "------------------------------\n";
    report_file << std::left << std::setw(12) << "Instância" << std::setw(16) << "Guloso";
    for (double alpha : alpha_values) report_file << std::setw(18) << ("Rand(" + std::to_string(alpha) + ")");
    report_file << std::setw(16) << "Reativo" << "\n";
    report_file << std::string(70, '-') << "\n";
    for (const auto& pair : best_solutions) {
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
    std::cout << "Relatório gerado em 'relatorio_resultados.txt'\n";
}

int main(int argc, char* argv[]) {
    // Sempre carrega o menu interativo do Gerenciador
    std::string path;
    std::cout << "Digite o caminho do arquivo de grafo para o menu interativo (ex: instancias_t2/grafo-t2-1.txt): ";
    std::getline(std::cin, path);
    Grafo* grafo = new Grafo(path.c_str());
    Gerenciador::comandos(grafo);
    delete grafo;
    return 0;
}