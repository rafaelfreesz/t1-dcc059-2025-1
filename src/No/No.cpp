#include "No.h"

No::No() : id(0), peso(0) {}

No::No(char id, int peso) : id(id), peso(peso) {}

No::~No() {
    for (Aresta* a : arestas) {
        delete a;
    }
}