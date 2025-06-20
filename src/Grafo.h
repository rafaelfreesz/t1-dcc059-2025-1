//
// Created by Rafael on 28/05/2025.
//

#ifndef GRAFO_H
#define GRAFO_H

#include "No.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>
#include <climits>

using namespace std;

class Grafo {
public:

    // construtores e destrutores
    Grafo();
    Grafo(bool direcionado, bool ponderado_vertice, bool ponderado_aresta);
    ~Grafo();

    // funções para implementar
    vector<char> fecho_transitivo_direto(char id_no); // a RESOLVIDO
    vector<char> fecho_transitivo_indireto(char id_no); // b RESOLVIDO
    vector<char> caminho_minimo_dijkstra(char id_no_a, char id_no_b); // c
    vector<char> caminho_minimo_floyd(char id_no, char id_no_b); // d
    Grafo* arvore_geradora_minima_prim(vector<char> ids_nos); // e
    Grafo* arvore_geradora_minima_kruskal(vector<char> ids_nos); // f
    Grafo* arvore_caminhamento_profundidade(char id_no); // g
    int raio(); // h 1
    int diametro(); // h 2
    vector<char> centro(); // h 3
    vector<char> periferia(); // h 4
    vector<char> vertices_de_articulacao(); // i

    // variaveis do grafo
    int ordem;
    bool in_direcionado;
    bool in_ponderado_aresta;
    bool in_ponderado_vertice;
    vector<No*> lista_adj;

    // funcoes adicionais de classe
    void adicionarNo(char idNovoNo, int pesoNovoNo);
    void adicionarAresta(char origemID, char destinoID, int peso);
    string toString();
  
private:
    No* getNo(char id);
    void fecho_transitivo_direto_aux(char id_no, map<char, bool> &visitados, vector<char> &resultado);
    void fecho_transitivo_indireto_aux(char id_no, map<char, bool> &visitados, vector<char> &resultado);
    void dijkstra_aux(char noAtual, map<char, int> &distancias, map<char, char> &predecessores);
};



#endif //GRAFO_H
