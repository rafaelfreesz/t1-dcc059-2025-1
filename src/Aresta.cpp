#include "Aresta.h"

Aresta::Aresta(char id_no_origem, char id_no_alvo, int peso)
{
    this->id_no_origem = id_no_origem;
    this->id_no_alvo = id_no_alvo;
    this->peso = peso;
}

Aresta::~Aresta()
{

}

char Aresta::getIdOrigem()
{
    return this->id_no_origem;
}

char Aresta::getIdAlvo()
{
    return this->id_no_alvo;
}

int Aresta::getPeso()
{
    return this->peso;
}

void Aresta::setIdOrigem(char id_no_origem)
{
    this->id_no_origem = id_no_origem;
}

void Aresta::setIdAlvo(char id_no_alvo)
{
    this->id_no_alvo = id_no_alvo;
}

void Aresta::setPeso(int peso)
{
    this->peso = peso;
}