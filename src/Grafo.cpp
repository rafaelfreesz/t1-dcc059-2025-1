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
    struct prox{
        char id_no_proximo;
        int custo;
    };

    map<char, prox> map_prox; // mapa para armazenar o próximo nó e seu custo
    for(char id_no : ids_nos) {
        map_prox[id_no] = {ids_nos[0], INT_MAX}; // inicializa o mapa com custo infinito
    }

    Grafo *resultado = new Grafo(); // grafo resultado
    resultado->in_direcionado = this->in_direcionado;
    resultado->in_ponderado_aresta = this->in_ponderado_aresta;
    resultado->in_ponderado_vertice = this->in_ponderado_vertice;
    resultado->ordem = ids_nos.size();

    // cria o nó inicial e adiciona ao grafo resultado
    No *no_inicial = new No(ids_nos[0], getNo(ids_nos[0])->getPeso());
    resultado->lista_adj.push_back(no_inicial);
    map_prox[ids_nos[0]] = {'\0', INT_MAX}; // marca no incial como resolvido

    
    No *no_atual = getNo(ids_nos[0]);
    int cont = 1; // contador de nós adicionados
    while(cont < ids_nos.size()) {
        for(Aresta *aresta : no_atual->arestas) {
            char id_no_alvo = aresta->getIDalvo();
            if(find(ids_nos.begin(), ids_nos.end(), id_no_alvo) != ids_nos.end()) {
                if(map_prox[id_no_alvo].custo > aresta->getPeso() and map_prox[id_no_alvo].id_no_proximo != '\0') {
                    // Atualiza o mapa de próximos se o custo for menor
                    map_prox[id_no_alvo] = {no_atual->getID(), aresta->getPeso()};
                }
            }
        }

        auto it = min_element(map_prox.begin(), map_prox.end(),
            [](const pair<char, prox> &a, const pair<char, prox> &b) {
                return a.second.custo < b.second.custo;
            });
        
        // Adiciona o nó com aresta de menor custo ao grafo resultado
        No *novo_no = new No(it->first, getNo(it->first)->getPeso());
        Aresta *nova_aresta = new Aresta(it->second.id_no_proximo, it->second.custo);
        novo_no->adicionarAresta(nova_aresta);
        resultado->lista_adj.push_back(novo_no);
        if(!resultado->in_direcionado) {
            // se o grafo nao for direcionado, adiciona a aresta inversa
            No *no_alvo = resultado->getNo(it->second.id_no_proximo);
            Aresta *nova_aresta_inversa = new Aresta(it->first, it->second.custo);
            no_alvo->adicionarAresta(nova_aresta_inversa);
        }
        
        no_atual = getNo(it->first); // atualiza o nó atual
        
        map_prox[it->first] = {'\0', INT_MAX}; // marca o nó atual como resolvido
        
        cont++;
    }
    
    
    return resultado;
}

Grafo *Grafo::arvore_geradora_minima_kruskal(vector<char> ids_nos)
{

    // "pacote" que engloba o no de inicio de uma aresta e a aresta em si
    struct ArestaInicioFim
    {
        char id_inicio;
        Aresta *aresta;
    };

    vector<ArestaInicioFim *> arestas;
    Grafo *resultado = new Grafo();
    resultado->in_direcionado = this->in_direcionado;
    resultado->in_ponderado_aresta = this->in_ponderado_aresta;
    resultado->in_ponderado_vertice = this->in_ponderado_vertice;
    resultado->ordem = ids_nos.size();
    for (char ind : ids_nos)
    {
        auto it = find_if(lista_adj.begin(), lista_adj.end(), // procura pelo no na lista de adjacencia
                          [ind](const No *no)
                          {
                              return no->id == ind;
                          });

        if (it != lista_adj.end()) // verifica se o no foi ecnontrado
        {
            No *no = *it;

            // cria as |v| subarvores de nós isolados
            No *no_isolado = new No(no->id, no->peso);
            resultado->lista_adj.push_back(no_isolado);

            for (Aresta *aresta : no->arestas)
            {
                // verifica se a aresta aponta para um no que esta no ids_nos
                auto it_alvo = find_if(ids_nos.begin(), ids_nos.end(),
                                       [aresta](char id_alvo)
                                       {
                                           return id_alvo == aresta->id_no_alvo;
                                       });
                if (it_alvo == ids_nos.end()) // se o no alvo nao esta no ids_nos, pula para a proxima aresta
                    continue;

                if (in_direcionado ||                       // se o grafo for direcionado, adiciona todas as arestas
                    find_if(arestas.begin(), arestas.end(), // caso contrario, verifica se a aresta ja foi adicionada
                            [aresta, no](const ArestaInicioFim *a)
                            {
                                return (a->id_inicio == aresta->id_no_alvo && a->aresta->id_no_alvo == no->id);
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

    int cont = 0; // contador de arestas adicionadas
    while (cont < resultado->ordem - 1 && !arestas.empty())
    {
        ArestaInicioFim *aresta_inicio_fim = arestas.front();
        arestas.erase(arestas.begin()); // remove a aresta do vetor

        vector<char> fecho_direto = resultado->fecho_transitivo_direto(aresta_inicio_fim->id_inicio);

        if (find(fecho_direto.begin(), fecho_direto.end(), aresta_inicio_fim->aresta->id_no_alvo) == fecho_direto.end())
        {
            // se o no alvo da aresta não é alcançado pelo no de inicio, adiciona a aresta ao grafo resultado
            No *no_inicio = resultado->getNo(aresta_inicio_fim->id_inicio);
            Aresta *nova_aresta = new Aresta(aresta_inicio_fim->aresta->id_no_alvo, aresta_inicio_fim->aresta->peso);
            no_inicio->adicionarAresta(nova_aresta);

            if (!resultado->in_direcionado)
            {
                // se o grafo nao for direcionado, adiciona a aresta inversa
                No *no_alvo = resultado->getNo(aresta_inicio_fim->aresta->id_no_alvo);
                Aresta *nova_aresta_inversa = new Aresta(aresta_inicio_fim->id_inicio, aresta_inicio_fim->aresta->peso);
                no_alvo->adicionarAresta(nova_aresta_inversa);
            }

            cont++;
        }
    }
    return resultado;
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

string Grafo::toString() {
    
    struct ArestaInicioFim {
        char id_inicio;
        Aresta* aresta;
    };
    
    stringstream ss;
    ss << "Grafo: " << endl;
    ss << (in_direcionado ? "1" : "0") << " ";
    ss << (in_ponderado_aresta ? "1" : "0") << " ";
    ss << (in_ponderado_vertice ? "1" : "0") << endl;
    ss << ordem << endl;

    for (No* no : lista_adj) {
        ss << no->getID();
        if (in_ponderado_vertice) {
            ss << " " << no->getPeso();
        }
        ss << endl;
    }

    vector<ArestaInicioFim*> arestas;
    for(No* no : lista_adj) {
        for(Aresta* aresta : no->arestas) {
            auto it = find_if(arestas.begin(), arestas.end(),
            [aresta, no](const ArestaInicioFim* a)
            {
                return a->id_inicio == aresta->id_no_alvo
                && a->aresta->id_no_alvo == no->getID();
            });

            if (it == arestas.end() || in_direcionado) {
                ss << no->getID() << " " << aresta->getIDalvo();
                if (in_ponderado_aresta) {
                    ss << " " << aresta->getPeso();
                }
                ss << endl;
                ArestaInicioFim* aresta_inicio_fim = new ArestaInicioFim();
                aresta_inicio_fim->id_inicio = no->getID();
                aresta_inicio_fim->aresta = aresta;
                arestas.push_back(aresta_inicio_fim);
            }
        }
    }
    return ss.str();
}
