#include "Grafo.h"
#include <set>


Grafo::Grafo() {
    ordem = 0;
    in_direcionado = false;
    in_ponderado_aresta = false;
    in_ponderado_vertice = false;
    lista_adj = vector<No*>();
}

void aux_dfs(No* no, set<char>& visitado) {
    if (visitado.find(no->id) == visitado.end()) {
        visitado.insert(no->id);
        for (No* vizinho : no->vizinhos) {
            aux_dfs(vizinho, visitado);
        }
    }
}

Grafo::~Grafo() {
}

vector<char> Grafo::fecho_transitivo_direto(int id_no) {
    No* origem = nullptr;
    for (No* no : lista_adj) {
        if (no->id == id_no) {
            origem = no;
            break;
        }
    }
    if (origem == nullptr) {
        cout << "No com id " << id_no << " nao encontrado." << endl;
        return {};
    }
    set<char> visitado;
    aux_dfs(origem, visitado);
    vector<char> resultado(visitado.begin(), visitado.end());
    return resultado; //talvez esteja certo, nao sei >>vale rever<<

    cout<<"Metodo nao implementado"<<endl;
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
