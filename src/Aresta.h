#ifndef ARESTA_H
#define ARESTA_H

using namespace std;
class Aresta {
public:
    Aresta();
    ~Aresta();

    char id_no_alvo;
    int peso;

    int getPeso();
    void setPeso(int peso);
    
};



#endif //ARESTA_H
