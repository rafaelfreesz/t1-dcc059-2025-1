#include "SolucionadorEDS.h"
#include <algorithm>
#include <random>

SolucionadorEDS::SolucionadorEDS(Grafo* grafo) : grafo(grafo) {}

SolucionadorEDS::~SolucionadorEDS() {}

// Função auxiliar: calcula o poder de dominância de uma aresta
int SolucionadorEDS::poderDominancia(const std::pair<char, char>& aresta, const std::vector<std::pair<char, char>>& arestasNaoDominadas) const {
    int poder = 0;
    for (const auto& a : arestasNaoDominadas) {
        if (a == aresta) {
            poder++;
            continue;
        }
        // Se compartilha um vértice
        if (a.first == aresta.first || a.second == aresta.first || a.first == aresta.second || a.second == aresta.second) {
            poder++;
        }
    }
    return poder;
}

// Fase 1: Algoritmo Guloso
std::vector<std::pair<char, char>> SolucionadorEDS::executarGuloso() {
    std::vector<std::pair<char, char>> S;
    std::vector<std::pair<char, char>> arestasNaoDominadas = grafo->getTodasArestas();
    while (!arestasNaoDominadas.empty()) {
        int maxDominancia = -1;
        std::pair<char, char> melhorAresta;
        for (const auto& aresta : arestasNaoDominadas) {
            int dominancia = poderDominancia(aresta, arestasNaoDominadas);
            if (dominancia > maxDominancia) {
                maxDominancia = dominancia;
                melhorAresta = aresta;
            }
        }
        S.push_back(melhorAresta);
        // Remove todas as arestas dominadas por melhorAresta
        std::vector<std::pair<char, char>> novasNaoDominadas;
        for (const auto& a : arestasNaoDominadas) {
            if (!(a == melhorAresta) && !(a.first == melhorAresta.first || a.second == melhorAresta.first || a.first == melhorAresta.second || a.second == melhorAresta.second)) {
                novasNaoDominadas.push_back(a);
            }
        }
        arestasNaoDominadas = novasNaoDominadas;
    }
    return S;
}

// Fase 2: Guloso Randomizado Adaptativo (GRASP/GRA)
std::vector<std::pair<char, char>> SolucionadorEDS::executarGRA(int numIteracoes, int semente, double alpha) {
    std::vector<std::pair<char, char>> melhorSolucao;
    int melhorTamanho = -1;
    std::mt19937 rng(semente);
    for (int it = 0; it < numIteracoes; ++it) {
        std::vector<std::pair<char, char>> S_iter;
        std::vector<std::pair<char, char>> arestasNaoDominadas = grafo->getTodasArestas();
        while (!arestasNaoDominadas.empty()) {
            // Calcula dominância de cada aresta
            int maxDominancia = -1;
            std::vector<std::pair<char, char>> candidatos;
            std::vector<int> dominancias;
            for (const auto& aresta : arestasNaoDominadas) {
                int dominancia = poderDominancia(aresta, arestasNaoDominadas);
                dominancias.push_back(dominancia);
                if (dominancia > maxDominancia) maxDominancia = dominancia;
            }
            // Monta RCL
            for (size_t i = 0; i < arestasNaoDominadas.size(); ++i) {
                if (dominancias[i] >= alpha * maxDominancia) {
                    candidatos.push_back(arestasNaoDominadas[i]);
                }
            }
            // Seleciona aleatoriamente da RCL
            std::uniform_int_distribution<int> dist(0, (int)candidatos.size() - 1);
            auto escolhida = candidatos[dist(rng)];
            S_iter.push_back(escolhida);
            // Remove todas as arestas dominadas pela escolhida
            std::vector<std::pair<char, char>> novasNaoDominadas;
            for (const auto& a : arestasNaoDominadas) {
                if (!(a == escolhida) && !(a.first == escolhida.first || a.second == escolhida.first || a.first == escolhida.second || a.second == escolhida.second)) {
                    novasNaoDominadas.push_back(a);
                }
            }
            arestasNaoDominadas = novasNaoDominadas;
        }
        if (melhorTamanho == -1 || (int)S_iter.size() < melhorTamanho) {
            melhorTamanho = (int)S_iter.size();
            melhorSolucao = S_iter;
        }
    }
    return melhorSolucao;
}

// Fase 3: Guloso Randomizado Adaptativo Reativo (GRAR)
std::vector<std::pair<char, char>> SolucionadorEDS::executarGRAR(int numIteracoes, int semente) {
    // Alphas possíveis e probabilidades
    std::vector<double> alphas = {0.1, 0.2, 0.3, 0.4};
    std::vector<double> probs(alphas.size(), 1.0 / alphas.size());
    std::vector<double> qualidades(alphas.size(), 0.0);
    std::vector<int> usos(alphas.size(), 0);
    std::mt19937 rng(semente);
    std::vector<std::pair<char, char>> melhorSolucao;
    int melhorTamanho = -1;
    int bloco = 50; // A cada bloco de iterações, ajusta as probabilidades
    for (int it = 0; it < numIteracoes; ++it) {
        // Escolhe alpha conforme as probabilidades
        std::discrete_distribution<int> distProb(probs.begin(), probs.end());
        int idxAlpha = distProb(rng);
        double alpha = alphas[idxAlpha];
        // Executa uma construção gulosa randomizada com esse alpha
        std::vector<std::pair<char, char>> S_iter;
        std::vector<std::pair<char, char>> arestasNaoDominadas = grafo->getTodasArestas();
        while (!arestasNaoDominadas.empty()) {
            int maxDominancia = -1;
            std::vector<std::pair<char, char>> candidatos;
            std::vector<int> dominancias;
            for (const auto& aresta : arestasNaoDominadas) {
                int dominancia = poderDominancia(aresta, arestasNaoDominadas);
                dominancias.push_back(dominancia);
                if (dominancia > maxDominancia) maxDominancia = dominancia;
            }
            for (size_t i = 0; i < arestasNaoDominadas.size(); ++i) {
                if (dominancias[i] >= alpha * maxDominancia) {
                    candidatos.push_back(arestasNaoDominadas[i]);
                }
            }
            std::uniform_int_distribution<int> dist(0, (int)candidatos.size() - 1);
            auto escolhida = candidatos[dist(rng)];
            S_iter.push_back(escolhida);
            std::vector<std::pair<char, char>> novasNaoDominadas;
            for (const auto& a : arestasNaoDominadas) {
                if (!(a == escolhida) && !(a.first == escolhida.first || a.second == escolhida.first || a.first == escolhida.second || a.second == escolhida.second)) {
                    novasNaoDominadas.push_back(a);
                }
            }
            arestasNaoDominadas = novasNaoDominadas;
        }
        // Atualiza qualidade
        double qualidade = 1.0 / S_iter.size();
        qualidades[idxAlpha] += qualidade;
        usos[idxAlpha]++;
        if (melhorTamanho == -1 || (int)S_iter.size() < melhorTamanho) {
            melhorTamanho = (int)S_iter.size();
            melhorSolucao = S_iter;
        }
        // Ajusta probabilidades a cada bloco
        if ((it + 1) % bloco == 0) {
            double soma = 0.0;
            for (size_t i = 0; i < alphas.size(); ++i) {
                if (usos[i] > 0) {
                    probs[i] = qualidades[i] / usos[i];
                } else {
                    probs[i] = 1.0;
                }
                soma += probs[i];
            }
            for (double& p : probs) p /= soma;
        }
    }
    return melhorSolucao;
}
