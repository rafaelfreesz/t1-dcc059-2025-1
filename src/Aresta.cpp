#include "Aresta.h"

Aresta::Aresta(char idAlvo, int peso){
    setIDalvo(idAlvo);
    setPeso(peso);
}

Aresta::~Aresta(){

}

char Aresta::getIDalvo(){
    return id_no_alvo;
}

void Aresta::setIDalvo(char novoID){
    this->id_no_alvo = novoID;
}

int Aresta::getPeso(){
    return this->peso;
}

void Aresta::setPeso(int peso){
    this->peso = peso;
}