#ifndef ARESTA_H
#define ARESTA_H

class Aresta {
public:
    char id_no_alvo; // compatível com Grafo
    int peso;

    Aresta();
    Aresta(char id_no_alvo, int peso = 1);
    ~Aresta();
};

#endif // ARESTA_H