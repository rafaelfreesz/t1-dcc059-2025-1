#include "No.h"

No::No(char id, int peso, vector<Aresta *> arestas)
{
    this->id = id;
    this->peso = peso;
    this->arestas = arestas;
}

No::~No()
{
    for(Aresta* aresta : arestas)
    {
        delete aresta;
    }
}

vector<Aresta *> No::getAresta()
{
    return this->arestas;
}

char No::getId()
{
    return this->id;
}

int No::getPeso()
{
    return this->peso;
}

void No::setAresta(Aresta *aresta)
{
    arestas.emplace_back(aresta);
}

void No::setArestas(vector<Aresta *> arestas)
{
    this->arestas = arestas;
}

void No::setId(char id)
{
    this->id = id;
}

void No::setPeso(int peso)
{
    this->peso = peso;
}