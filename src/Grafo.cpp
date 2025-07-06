#include "Grafo.h"


Grafo::Grafo(int ordem, bool in_direcionado, bool in_ponderado_aresta, bool in_ponderado_vertice, vector<No*> lista_adj) {
    this->ordem = ordem;
    this->in_direcionado = in_direcionado;
    this->in_ponderado_aresta = in_ponderado_aresta;
    this->in_ponderado_vertice = in_ponderado_vertice;
    this->lista_adj = lista_adj;
}

Grafo::~Grafo() {
}

vector<No*> Grafo::getListaAdj()
{
    return lista_adj;
}

int Grafo::getOrdem()
{
    return ordem;
}

vector<char> Grafo::fecho_transitivo_direto(int id_no) {
    vector<char> visitados;
    vector<char> pilha;

    pilha.push_back((char)id_no);

    while (!pilha.empty()) {
        char atual_id = pilha.back();
        pilha.pop_back();

        No* atual = 0;
        for (int i = 0; i < lista_adj.size(); i++) {
            if (lista_adj[i]->getId() == atual_id) {
                atual = lista_adj[i];
                break;
            }
        }

        if (atual == 0) continue;

        vector<Aresta*> arestas = atual->getArestas();

        for (int i = 0; i < arestas.size(); i++) {
            char id_destino = arestas[i]->getIdAlvo();

            bool ja_visitado = false;
            for (int j = 0; j < visitados.size(); j++) {
                if (visitados[j] == id_destino) {
                    ja_visitado = true;
                    break;
                }
            }

            if (!ja_visitado) {
                visitados.push_back(id_destino);
                pilha.push_back(id_destino);
            }
        }
    }

    return visitados;
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
