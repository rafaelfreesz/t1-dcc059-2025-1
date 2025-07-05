#ifndef GRAFO_H
#define GRAFO_H

#include "../No/No.h"
#include "../Aresta/Aresta.h"
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string> // Necessário para const char* no construtor

using namespace std;

// Forward declaration de No e Aresta se não houver inclusão mútua complexa
// class No;
// class Aresta;

class Grafo {
public:
    // Construtor vazio para subgrafos ou grafos construídos programaticamente 
    Grafo();
    // Construtor que lê o grafo de um arquivo de entrada [cite: 7]
    Grafo(const char* arquivoEntrada);
    // Destrutor para liberar a memória alocada 
    ~Grafo();

    // Funcionalidades principais [cite: 23, 24, 26, 27, 28, 29, 30, 31]
    vector<char> fecho_transitivo_direto(char id_no); // a
    vector<char> fecho_transitivo_indireto(char id_no); // b
    vector<char> caminho_minimo_dijkstra(char id_no_a, char id_no_b); // c
    vector<char> caminho_minimo_floyd(char id_no_a, char id_no_b); // d
    Grafo* arvore_geradora_minima_prim(vector<char> ids_nos); // e
    Grafo* arvore_geradora_minima_kruskal(vector<char> ids_nos); // f
    Grafo* arvore_caminhamento_profundidade(char id_no); // g
    int raio(); // h 1
    int diametro(); // h 2
    vector<char> centro(); // h 3
    vector<char> periferia(); // h 4
    // vector<char> vertices_de_articulacao(); // removido conforme instrução, pois não é mais 'i' e não faz parte do escopo final da entrega 'h'

    // Métodos de manipulação do grafo 
    void insereNo(char id, int peso = 0);
    void insereAresta(char origem, char destino, int pesoAresta = 1); // Removido pesoNo pois não é usado nas arestas diretamente 

    // Atributos do grafo [cite: 12, 11, 4, 2]
    int ordem; // Número de vértices [cite: 12]
    bool in_direcionado; // Se é direcionado [cite: 11]
    bool in_ponderado_aresta; // Se é ponderado nas arestas [cite: 11]
    bool in_ponderado_vertice; // Se é ponderado nos vértices [cite: 11]
    vector<No*> lista_adj; // Lista de adjacência 

    // Método auxiliar para obter um nó pelo ID 
    No* getNo(char id);

    // Método para verificar se o grafo é conexo (usado para AGM) 
    bool ehConexo();

private:
    // DFS auxiliar para fecho transitivo direto
    void dfs_fecho_direto(char u, std::set<char>& visitado);
    // DFS auxiliar para fecho transitivo indireto (neste caso, é mais fácil construir um grafo reverso e fazer DFS direta)
    void dfs_fecho_indireto(char u, std::set<char>& visitado, const std::map<char, std::vector<char>>& grafo_reverso);
    // DFS auxiliar para árvore de caminhamento em profundidade [cite: 30]
    void dfs_arvore_caminhamento(char u, std::set<char>& visitado, Grafo* arvore_dfs, std::set<pair<char, char>>& arestas_arvore);
};

#endif // GRAFO_H