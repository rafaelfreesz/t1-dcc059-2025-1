#ifndef NO_H
#define NO_H

#include <vector>
#include "../Aresta/Aresta.h"

class Aresta;

class No {
public:
    char id; // Usar char para compatibilidade com Grafo
    int peso;
    std::vector<Aresta*> arestas;

    No();
    No(char id, int peso = 0);
    ~No();
};

#endif // NO_H