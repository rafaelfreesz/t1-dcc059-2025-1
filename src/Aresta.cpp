#include "Aresta.h"

Aresta::Aresta(){
    setPeso(0);
}

Aresta::~Aresta(){

}

int Aresta::getPeso(){
    return this->peso;
}

void Aresta::setPeso(int peso){
    this->peso = peso;
}