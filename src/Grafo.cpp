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
    vector<char> resultado;

    for (int i = 0; i < lista_adj.size(); i++) {
        char id_atual = lista_adj[i]->getId();

        if (id_atual == id_no) continue;

        vector<char> visitados;
        vector<char> pilha;
        pilha.push_back(id_atual);

        while (!pilha.empty()) {
            char topo = pilha.back();
            pilha.pop_back();

            bool ja_foi = false;
            for (int v = 0; v < visitados.size(); v++) {
                if (visitados[v] == topo) {
                    ja_foi = true;
                    break;
                }
            }
            if (ja_foi) continue;

            visitados.push_back(topo);

            if (topo == id_no) {
                resultado.push_back(id_atual);
                break;
            }

            // Encontrar o nó correspondente ao topo
            No* no_topo = 0;
            for (int j = 0; j < lista_adj.size(); j++) {
                if (lista_adj[j]->getId() == topo) {
                    no_topo = lista_adj[j];
                    break;
                }
            }

            if (no_topo != 0) {
                vector<Aresta*> arestas = no_topo->getArestas();
                for (int k = 0; k < arestas.size(); k++) {
                    char id_destino = arestas[k]->getIdAlvo();
                    pilha.push_back(id_destino);
                }
            }
        }
    }

    return resultado;
}

vector<char> Grafo::caminho_minimo_dijkstra(int id_no_a, int id_no_b) {
    const int INF = 1000000;
    vector<char> vertices;

    // Passo 1: extrair todos os IDs
    for (int i = 0; i < lista_adj.size(); i++) {
        vertices.push_back(lista_adj[i]->getId());
    }

    // Passo 2: inicializar distâncias e visitados
    int dist[256];       // índice pelo valor ASCII do ID
    bool visitado[256] = {false};
    char anterior[256];  // para reconstruir caminho

    for (int i = 0; i < 256; i++) {
        dist[i] = INF;
        anterior[i] = '\0';
    }

    dist[(int)id_no_a] = 0;

    while (true) {
        // Encontrar o vértice não visitado com menor distância
        char atual = '\0';
        int menor_dist = INF;

        for (int i = 0; i < vertices.size(); i++) {
            char id = vertices[i];
            if (!visitado[(int)id] && dist[(int)id] < menor_dist) {
                menor_dist = dist[(int)id];
                atual = id;
            }
        }

        if (atual == '\0') break; // nenhum vértice restante
        if (atual == id_no_b) break; // destino encontrado

        visitado[(int)atual] = true;

        // Acessar vizinhos de 'atual'
        No* no_atual = nullptr;
        for (int i = 0; i < lista_adj.size(); i++) {
            if (lista_adj[i]->getId() == atual) {
                no_atual = lista_adj[i];
                break;
            }
        }

        if (no_atual == nullptr) continue;

        vector<Aresta*> arestas = no_atual->getArestas();
        for (int j = 0; j < arestas.size(); j++) {
            char vizinho = arestas[j]->getIdAlvo();
            int peso = arestas[j]->getPeso();

            if (dist[(int)vizinho] > dist[(int)atual] + peso) {
                dist[(int)vizinho] = dist[(int)atual] + peso;
                anterior[(int)vizinho] = atual;
            }
        }
    }

    // Reconstruir caminho
    vector<char> caminho;
    char atual = id_no_b;

    while (atual != '\0') {
        caminho.insert(caminho.begin(), atual);
        atual = anterior[(int)atual];
    }

    // Se não encontrou o destino, o primeiro não será o de origem
    if (caminho.size() == 0 || caminho[0] != id_no_a) {
        return {}; // caminho inexistente
    }

    return caminho;
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
