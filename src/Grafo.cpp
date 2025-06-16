#include "Grafo.h"


Grafo::Grafo() {
}

Grafo::~Grafo() {
}

//TODO: Procurar saber se o char é aleatório ou se segue como um número
No* Grafo::getNo(char id) {
    for (No* no : lista_adj) {
        if (no->getID() == id) {
            return no;
        }
    }
    //TODO: Tratar erro melhor
    cout << "No com id " << id << " nao encontrado." << endl;
    exit(1);
}


vector<char> Grafo::fecho_transitivo_direto(char id_no) {
    map<char, bool> visitados;
    vector<char> resultado;
    fecho_transitivo_direto_aux(id_no, visitados, resultado);
    return resultado;
}

void Grafo::fecho_transitivo_direto_aux(char id_no, map<char, bool> &visitados, vector<char> &resultado) {
    No* no = getNo(id_no);
    for(const auto& aresta : no->arestas) {
        char id_alvo = aresta->id_no_alvo;
        if(!visitados[id_alvo]){
            visitados[id_alvo] = true;
            resultado.push_back(id_alvo);
            fecho_transitivo_direto_aux(id_alvo, visitados, resultado);
        }
    }
    
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
