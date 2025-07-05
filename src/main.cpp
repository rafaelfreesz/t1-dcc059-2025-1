#include <iostream>
#include "Gerenciador.h"
#include "Grafo.h"

using namespace std;
int main(int argc, char *argv[])
{
    vector<Aresta*> arestas;
    No* a = new No('a', 0, arestas);
    vector<No*> lista_adj;
    lista_adj.push_back(a);
    Grafo* grafo = new Grafo(5, 0, 0, 0, lista_adj);

    Gerenciador::comandos(grafo);

    return 0;
}
