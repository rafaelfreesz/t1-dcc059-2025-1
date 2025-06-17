#include "Grafo.h"


Grafo::Grafo(){
    
}

Grafo::Grafo(bool direcionado, bool ponderado_vertice, bool ponderado_aresta) {
    this->in_direcionado = direcionado;
    this->in_ponderado_vertice = ponderado_vertice;
    this->in_ponderado_aresta = ponderado_aresta;
    this->ordem = 0; // tem 0 vertices inicialmente
}

Grafo::~Grafo() {
    for(No* no : lista_adj){
        delete no;
    }
}

void Grafo::adicionarNo(char idNovoNo, int pesoNovoNo){
    No* novoNo = new No(idNovoNo, in_ponderado_vertice? pesoNovoNo : 0);
    lista_adj.push_back(novoNo);
    ordem++;
}

void Grafo::adicionarAresta(char origemID, char destinoID, int peso){
    No* no1 = nullptr;
    No* no2 = nullptr;

    for(int i=0; i < lista_adj.size(); i++){
        if(lista_adj[i]->getID() == origemID)
            no1 = lista_adj[i];
        if(lista_adj[i]->getID() == destinoID)
            no2 = lista_adj[i];
    // verifica os IDs de cada nó da lista e atribui corretamente se existirem
    }

    if(!no1 || !no2){
        cout<<"Erro: vertice nao encontrado"<<endl;
        return;
        // erro se um dos nós não estiver no grafo
    }

    int peso_aresta = in_ponderado_aresta? peso : 1;
    Aresta* novaAresta = new Aresta(destinoID, peso_aresta);
    // cria a aresta apontando para o destino
    no1->adicionarAresta(novaAresta);
    // adiciona aresta ao nó de origem

    if(!in_direcionado){
        Aresta* arestaInversa = new Aresta(origemID, peso_aresta);
        no2->adicionarAresta(arestaInversa);
        // adiciona aresta inversa se o grafo não for direcionado
    }
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
