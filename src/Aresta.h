#ifndef ARESTA_H
#define ARESTA_H

using namespace std;
class Aresta {
public:
    Aresta(char idAlvo, int peso = 0);
    ~Aresta();

    // ID do nó pro qual ela aponta
    char id_no_alvo;
    int peso;

    char getIDalvo();
    void setIDalvo(char novoID);
    int getPeso();
    void setPeso(int peso);
    
};



#endif //ARESTA_H
