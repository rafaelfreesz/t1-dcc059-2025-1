#include "Grafo.h"
#include <fstream>
#include <iostream>
using namespace std;

Grafo::Grafo(const char* arquivoEntrada) {
    ifstream file(arquivoEntrada);
    if (!file.is_open()) {
        cout << "ERRO: Nao foi possivel abrir o arquivo de entrada." << endl;
        exit(1);
    }

    int digrafo, pesoNo, pesoAresta;
    file >> digrafo >> pesoNo >> pesoAresta;
    this->in_direcionado = digrafo == 1;
    this->in_ponderado_vertice = pesoNo == 1;
    this->in_ponderado_aresta = pesoAresta == 1;

    file >> this->ordem;

    for (int i = 0; i < this->ordem; ++i) {
        char id;
        int peso = 0;
        file >> id;
        if (this->in_ponderado_vertice) {
            file >> peso;
        }
        this->insereNo(id, peso);
    }

    char origem, destino;
    int pesoA = 1, pesoNoAresta = 0;
    while (file >> origem >> destino) {
        if (this->in_ponderado_aresta && this->in_ponderado_vertice) {
            file >> pesoA >> pesoNoAresta;
            this->insereAresta(origem, destino, pesoA, pesoNoAresta);
        } else if (this->in_ponderado_aresta) {
            file >> pesoA;
            this->insereAresta(origem, destino, pesoA);
        } else if (this->in_ponderado_vertice) {
            file >> pesoNoAresta;
            this->insereAresta(origem, destino, 1, pesoNoAresta);
        } else {
            this->insereAresta(origem, destino, 1);
        }
    }
    file.close();
}

Grafo::~Grafo() {
    for (No* no : lista_adj) {
        for (Aresta* aresta : no->arestas) {
            delete aresta;
        }
        delete no;
    }
}

void Grafo::insereNo(char id, int peso) {
    for (No* no : lista_adj) {
        if (no->id == id)
            return;
    }
    No* novo = new No();
    novo->id = id;
    novo->peso = peso;
    lista_adj.push_back(novo);
}

void Grafo::insereAresta(char origem, char destino, int pesoAresta, int /*pesoNo*/) {
    No* noOrigem = nullptr;
    No* noDestino = nullptr;
    for (No* no : lista_adj) {
        if (no->id == origem)
            noOrigem = no;
        if (no->id == destino)
            noDestino = no;
    }
    if (!noOrigem || !noDestino)
        return;

    Aresta* aresta = new Aresta();
    aresta->id_no_alvo = destino;
    aresta->peso = pesoAresta;
    noOrigem->arestas.push_back(aresta);

    if (!in_direcionado) {
        Aresta* aresta2 = new Aresta();
        aresta2->id_no_alvo = origem;
        aresta2->peso = pesoAresta;
        noDestino->arestas.push_back(aresta2);
    }
}

// Métodos de funcionalidades (não implementados)
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