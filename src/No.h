#ifndef NO_H
#define NO_H

#include <string>
#include <vector>
#include "Aresta.h"


using namespace std;
class No {

private:
    char id;
    int peso;
    vector<Aresta*> arestas;

public:
    No(char id, int peso, vector<Aresta*> arestas = {});
    ~No();

    vector<Aresta *> getArestas();
    char getId();
    int getPeso();

    void setAresta(Aresta *aresta);
    void setArestas(vector<Aresta *> arestas);
    void setId(char id);
    void setPeso(int peso);
    void adicionarAresta(Aresta* aresta);
};



#endif //NO_H
