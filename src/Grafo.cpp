#include "Grafo.h"
#include <set>


Grafo::Grafo() {
    ordem = 0;
    in_direcionado = false;
    in_ponderado_aresta = false;
    in_ponderado_vertice = false;
    lista_adj = vector<No*>();
    adj = vector<vector<int>>(ordem); // Initialize adjacency list with size 'ordem'
}

void adicionarAresta(int v, int u) {
        //adj[v].push_back(u);
    }

void dfs(int v, const vector<vector<int>>& adj, set<int>& visited) {
    for (int u : adj[v]) {
        if (visited.find(u) == visited.end()) {
            visited.insert(u);
            dfs(u, adj, visited);
        }
    }
}

    void dfs(int v, set<int>& visitado) {
        /*for (int u : adj[v]) {
            if (visitado.find(u) == visitado.end()) {
                visitado.insert(u);
                dfs(u, visitado);
            }
        }*/ 
    }

Grafo::~Grafo() {
}

vector<char> Grafo::fecho_transitivo_direto(int id_no) {


    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::fecho_transitivo_indireto(int id_no) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::caminho_minimo_dijkstra(int id_no_a, int id_no_b) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::caminho_minimo_floyd(int id_no, int id_no_b) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

Grafo * Grafo::arvore_geradora_minima_prim(vector<char> ids_nos) {
    cout<<"Metodo nao implementado"<<endl;
    return nullptr;
}

Grafo * Grafo::arvore_geradora_minima_kruskal(vector<char> ids_nos) {
    cout<<"Metodo nao implementado"<<endl;
    return nullptr;
}

Grafo * Grafo::arvore_caminhamento_profundidade(int id_no) {
    cout<<"Metodo nao implementado"<<endl;
    return nullptr;
}

int Grafo::raio() {
    cout<<"Metodo nao implementado"<<endl;
    return 0;
}

int Grafo::diametro() {
    cout<<"Metodo nao implementado"<<endl;
    return 0;
}

vector<char> Grafo::centro() {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::periferia() {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::vertices_de_articulacao() {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}
