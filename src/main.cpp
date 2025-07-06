#include <iostream>
#include "Gerenciador.h"
#include "Grafo.h"
#include "Aresta.h"

using namespace std;
int main(int argc, char *argv[])
{
    Aresta* a_b = new Aresta('A', 'B', 1);
    Aresta* a_d = new Aresta('A', 'D', 1);
    Aresta* b_c = new Aresta('B', 'C', 1);
    Aresta* b_e = new Aresta('B', 'E', 1);
    Aresta* c_e = new Aresta('C', 'E', 1);

    vector<Aresta*> arestas_a = {a_b, a_d};
    vector<Aresta*> arestas_b = {b_c, b_e};
    vector<Aresta*> arestas_c = {c_e};
    vector<Aresta*> arestas_d = {};
    vector<Aresta*> arestas_e = {};

    No* no_a = new No('A', 2, arestas_a);
    No* no_b = new No('B', 3, arestas_b);
    No* no_c = new No('C', 1, arestas_c);
    No* no_d = new No('D', 1, arestas_d);
    No* no_e = new No('E', 5, arestas_e);

    vector<No*> lista_adj = {no_a, no_b, no_c, no_d, no_e};

    Grafo* grafo = new Grafo(5, true, false, false, lista_adj);

    Gerenciador::comandos(grafo);

    return 0;
}
