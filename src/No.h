#ifndef NO_H
#define NO_H

#include <string>
#include <vector>
#include "Aresta.h"

using namespace std;

class No {
public:
    No(char id, int peso);
    ~No();

    char id;
    int peso;
    vector<Aresta*> arestas;

    int getPeso();
    void setPeso(int peso);
    char getID();
    void setID(char id);
};



#endif //NO_H
