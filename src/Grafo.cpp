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
    visitados[id_no] = true; // Marca o nó inicial como visitado
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
    map<char, bool> visitados;
    vector<char> resultado;
    visitados[id_no] = true; // Marca o nó inicial como visitado
    fecho_transitivo_indireto_aux(id_no, visitados, resultado);
    return resultado;
}

void Grafo::fecho_transitivo_indireto_aux(char id_no, map<char, bool> &visitados, vector<char> &resultado) {
    No* no = getNo(id_no);
    for(const auto& aresta : no->arestas_invertidas) {
        char id_alvo = aresta->id_no_alvo;
        if(!visitados[id_alvo]){
            visitados[id_alvo] = true;
            resultado.push_back(id_alvo);
            fecho_transitivo_indireto_aux(id_alvo, visitados, resultado);
        }
    }
}

vector<char> Grafo::caminho_minimo_dijkstra(char id_no_a, char id_no_b) {
    vector<char> caminho;
    map<char, int> distancias;
    distancias[id_no_a] = 0;
    map<char, char> predecessores;
    dijkstra_aux(id_no_a, distancias, predecessores);

    if (distancias.find(id_no_b) == distancias.end()) {
        return caminho; // Retorna vazio se nao houver caminho
    } else {
        char atual = id_no_b;
        while (atual != id_no_a) {
            caminho.push_back(atual);
            if (predecessores.find(atual) == predecessores.end()) {
                return {}; // Retorna vazio se nao houver caminho
            }
            atual = predecessores[atual];
        }
        caminho.push_back(id_no_a);
        reverse(caminho.begin(), caminho.end()); // Inverte o caminho para a ordem correta
    }

    return caminho;
}

void Grafo::dijkstra_aux(char noAtual, map<char, int> &distancias, map<char, char> &predecessores) {
    No* no = getNo(noAtual);

    for (const auto& aresta : no->arestas) {
        char id_alvo = aresta->id_no_alvo;
        int peso = aresta->getPeso();
        
        int nova_distancia = distancias[noAtual] + peso;
        if(distancias.find(id_alvo) == distancias.end() || nova_distancia < distancias[id_alvo]) {
            distancias[id_alvo] = nova_distancia;
            predecessores[id_alvo] = noAtual;
            dijkstra_aux(id_alvo, distancias, predecessores);
        }
    }
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
