#ifndef SOLUCIONADOREDS_H
#define SOLUCIONADOREDS_H

#include "../Grafo/Grafo.h"
#include <vector>
#include <utility>

class SolucionadorEDS {
public:
    SolucionadorEDS(Grafo* grafo);
    ~SolucionadorEDS();

    // Fase 1: Algoritmo Guloso
    std::vector<std::pair<char, char>> executarGuloso();

    // Fase 2: Guloso Randomizado Adaptativo (GRA)
    std::vector<std::pair<char, char>> executarGRA(int numIteracoes, int semente, double alpha = 0.3);

    // Fase 3: Guloso Randomizado Adaptativo Reativo (GRAR)
    std::vector<std::pair<char, char>> executarGRAR(int numIteracoes, int semente);

private:
    Grafo* grafo;
    // Função auxiliar: calcula o poder de dominância de uma aresta
    int poderDominancia(const std::pair<char, char>& aresta, const std::vector<std::pair<char, char>>& arestasNaoDominadas) const;
};

#endif // SOLUCIONADOREDS_H
