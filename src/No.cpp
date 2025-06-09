#include "No.h"

No::No(char id, int peso){
    setID(id);
    setPeso(peso);
}

No::~No(){
    for(int i=0;i<arestas.size(); i++){
        delete arestas[i];
    }
    delete this;
}

int No::getPeso(){
    return this->peso;
}

void No::setPeso(int peso){
    this->peso = peso;
}

char No::getID(){
    return this->id;
}

void No::setID(char id){
    this->id = id;
}