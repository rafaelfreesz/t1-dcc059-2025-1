#include "Grafo.h"


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
    
    // "pacote" que engloba o no de inicio de uma aresta e a aresta em si 
    struct ArestaInicioFim{
        char id_inicio;
        Aresta *aresta;
    };

    vector<ArestaInicioFim*> arestas;
    vector<Grafo*> subarvores;
    for(char ind : ids_nos)
    {
        auto it = find_if(lista_adj.begin(), lista_adj.end(), // procura pelo no na lista de adjacencia
                          [ind](const No *no)
                          {
                              return no->id == ind;
                          });

        if(it != lista_adj.end()) // verifica se o no foi ecnontrado 
        {
            No *no = *it;
            
            Grafo *subarvore = new Grafo();
            subarvore->in_direcionado = in_direcionado;
            subarvore->in_ponderado_aresta = in_ponderado_aresta;
            subarvore->in_ponderado_vertice = in_ponderado_vertice;
            subarvore->ordem = 1; // cada subarvore comeca com um no
            No *no_subarvore = new No(no->id, no->peso); // cria um novo com o mesmo id, mas sem arestas
            subarvore->lista_adj.push_back(no_subarvore); // adiciona o no na subarvore
            subarvores.push_back(subarvore); // adiciona a subarvore na lista de subarvores

            for(Aresta *aresta : no->arestas)
            {
                //verifica se a aresta aponta para um no que esta no ids_nos
                auto it_alvo = find_if(ids_nos.begin(), ids_nos.end(),
                                       [aresta](char id_alvo)
                                       {
                                           return id_alvo == aresta->id_no_alvo;
                                       });
                if(it_alvo == ids_nos.end()) // se o no alvo nao esta no ids_nos, pula para a proxima aresta
                    continue;

                if(in_direcionado || // se o grafo for direcionado, adiciona todas as arestas
                   find_if(arestas.begin(), arestas.end(), // caso contrario, verifica se a aresta ja foi adicionada
                            [aresta, no](const ArestaInicioFim *a)
                            {
                                return (a->id_inicio == aresta->id_no_alvo
                                        && a->aresta->id_no_alvo == no->id);
                            }) == arestas.end())
                {
                    ArestaInicioFim *aresta_inicio_fim = new ArestaInicioFim();
                    aresta_inicio_fim->id_inicio = no->id;
                    aresta_inicio_fim->aresta = aresta;
                    arestas.push_back(aresta_inicio_fim);
                }
            }
        }

    }

    // Ordena as arestas pelo peso
    sort(arestas.begin(), arestas.end(),
         [](const ArestaInicioFim *a, const ArestaInicioFim *b)
         {
             return a->aresta->peso < b->aresta->peso;
         });

    Grafo *arvore_minima = new Grafo();
    arvore_minima->in_direcionado = in_direcionado;
    arvore_minima->in_ponderado_aresta = in_ponderado_aresta;
    arvore_minima->in_ponderado_vertice = in_ponderado_vertice;
    arvore_minima->ordem = ids_nos.size();
    
    int cont = 0; // contador de arestas adicionadas

    while(cont < arvore_minima->ordem - 1 && !arestas.empty()) {
        ArestaInicioFim *aresta_inicio_fim = arestas.front();
        arestas.erase(arestas.begin()); // remove a aresta do vetor

        
    }
    
    
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
