#ifndef NO_H
#define NO_H

#include <string>
#include <vector>
#include "Aresta.h"


using namespace std;
class No {
    public:
        No(char id, int peso) : id(id), peso(peso){} //vertice ponderado
        No(char id) : id(id){} //vertice não ponderado
        ~No();

        // Getters
        char get_id() const;
        int get_peso() const;
        vector<Aresta*> get_arestas() const;
        vector<No*> get_vizinhos() const;

        // Setters
        void set_peso(int novo_peso);

    private:
        char id;
        int peso;
        vector<Aresta*> arestas;
        vector<No*> vizinhos;
};


#endif //NO_H
