#ifndef ARESTA_H
#define ARESTA_H

using namespace std;
class Aresta {
private:
    char id_no_origem;
    char id_no_alvo;
    int peso;

public:
    Aresta(char id_no_origem, char id_no_alvo, int peso);
    ~Aresta();

    char getIdOrigem();
    char getIdAlvo();
    int getPeso();
    void setIdOrigem(char id_no_origem);
    void setIdAlvo(char id_no_alvo);
    void setPeso(int peso);
};



#endif //ARESTA_H
