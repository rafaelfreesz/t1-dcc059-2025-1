#include <fstream>
#include <iostream>
#include <sstream>
#include "Grafo.h"
#include "No.h"
#include "Aresta.h"

using namespace std;

void Grafo::carregarGrafo(string nome_arquivo) {
    ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << nome_arquivo << endl;
        return;
    }

    int direcionado, ponderado_aresta, ponderado_vertice;
    arquivo >> direcionado >> ponderado_aresta >> ponderado_vertice;
    this->direcionado = direcionado;
    this->in_ponderado_aresta = ponderado_aresta;
    this->in_ponderado_vertice = ponderado_vertice;

    int num_vertices;
    arquivo >> num_vertices;
    this->ordem = num_vertices;

    for (int i = 0; i < num_vertices; ++i) {
        string linha;
        string id;
        int peso = 0;

        arquivo >> id;

        if (ponderado_vertice)
            arquivo >> peso;

        No *novo = new No();
        novo->id = id[0];
        novo->peso = peso;
        this->lista_adj.push_back(novo);
    }
    
    string id_a, id_b;
    int peso = 0;
    while (arquivo >> id_a >> id_b) {
        if (ponderado_aresta)
            arquivo >> peso;
        else
            peso = 0;

        No *origem = nullptr;
        for (No *no : lista-adj) {
            if (no->id == id_a[0]) {
                origem = no;
                break;
            }
        }

        if(prigem) {
            Aresta *aresta = new Aresta();
            aresta->id_no_alvo = id_b[0];
            aresta->peso = peso;
            origem->arestas.push_back(aresta);
        }

        if(!direcionado) {
            No *destino = nullptr;
            for (No *no : lista_adj) {
                if (no->id == id_b[0]) {
                    destino = no;
                    break;
                }
            }

            if (destino) {
                Aresta *aresta = new Aresta();
                aresta->id_no_alvo = id_a[0];
                aresta->peso = peso;
                destino->arestas.push_back(aresta);
            }
        }

    }

    arquivo.close();
}

Grafo::Grafo() {
}

Grafo::~Grafo() {
}

vector<char> Grafo::fecho_transitivo_direto(char id_no) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::fecho_transitivo_indireto(char id_no) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::caminho_minimo_dijkstra(char id_no_a, char id_no_b) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::caminho_minimo_floyd(char id_no, char id_no_b) {
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

Grafo * Grafo::arvore_caminhamento_profundidade(char id_no) {
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
