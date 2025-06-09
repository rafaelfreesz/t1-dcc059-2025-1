#ifndef ARESTA_H
#define ARESTA_H

using namespace std;
class Aresta {
public:
    Aresta();
    ~Aresta();

    // acho que é pra pegar o id do nó pro qual ela aponta
    char id_no_alvo;
    int peso;

    int getPeso();
    void setPeso(int peso);
    
};



#endif //ARESTA_H
