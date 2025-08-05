#include "Grafo.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
#include <tuple> // Para Kruskal (peso, origem, destino)
#include <numeric> // Para iota em DSU
#include <sstream> // Para stringstream

using namespace std;

// Construtor vazio (usado para subgrafos, etc.) 
Grafo::Grafo() {
    ordem = 0;
    in_direcionado = false;
    in_ponderado_aresta = false;
    in_ponderado_vertice = false;
}

// Construtor que lê o grafo de um arquivo de entrada
Grafo::Grafo(const char* arquivoEntrada) {
    ifstream file(arquivoEntrada);
    if (!file.is_open()) {
        cout << "ERRO CRITICO: Nao foi possivel abrir o arquivo: " << arquivoEntrada << endl;
        exit(1);
    }

    string linha;
    int digrafo, pesoNo, pesoAresta;

    // 1. Lê a primeira linha (flags)
    if (getline(file, linha)) {
        stringstream ss(linha);
        ss >> digrafo >> pesoAresta >> pesoNo;
        this->in_direcionado = (digrafo == 1);
        this->in_ponderado_aresta = (pesoAresta == 1);
        this->in_ponderado_vertice = (pesoNo == 1);
    }

    // 2. Lê a segunda linha (ordem)
    if (getline(file, linha)) {
        stringstream ss(linha);
        ss >> this->ordem;
    }

    // 3. Lê os 'ordem' próximos nós
    for (int i = 0; i < this->ordem && getline(file, linha); ++i) {
        stringstream ss(linha);
        char id;
        int peso = 0;
        ss >> id;
        if (this->in_ponderado_vertice) {
            ss >> peso;
        }
        this->insereNo(id, peso);
    }

    // 4. Lê as arestas até o final do arquivo
    char origem, destino;
    int pesoA = 1;
    while (getline(file, linha)) {
        // Ignora linhas vazias que podem existir no final do arquivo
        if (linha.empty() || linha.find_first_not_of(" \t\n\v\f\r") == string::npos) {
            continue;
        }
        
        stringstream ss(linha);
        if (ss >> origem >> destino) {
            if (this->in_ponderado_aresta) {
                ss >> pesoA;
            } else {
                pesoA = 1;
            }
            this->insereAresta(origem, destino, pesoA);
        }
    }
    file.close();
}

// Destrutor para liberar a memória alocada
Grafo::~Grafo() {
    for (No* no : lista_adj) {
        for (Aresta* aresta : no->arestas) {
            delete aresta;
        }
        delete no;
    }
}

// Retorna um ponteiro para o nó com o ID especificado, ou nullptr se não encontrado
No* Grafo::getNo(char id) {
    for (No* no : lista_adj)
        if (no->id == id)
            return no;
    return nullptr;
}

// Insere um novo nó no grafo 
void Grafo::insereNo(char id, int peso) {
    // Evita duplicatas
    if (getNo(id) != nullptr)
        return;

    No* novo = new No();
    novo->id = id;
    novo->peso = peso;
    lista_adj.push_back(novo);
    //ordem++; // Incrementa a ordem do grafo (Aparentemente isso nao é necessario e faz dupla.)
}

// Insere uma aresta entre dois nós 
void Grafo::insereAresta(char origem_id, char destino_id, int pesoAresta) {
    No* noOrigem = getNo(origem_id);
    No* noDestino = getNo(destino_id);

    
    if (!noOrigem || !noDestino) {
        // Um dos nós não existe, não é possível inserir a aresta
        return;
    }

    // Verifica se a aresta já existe para evitar duplicatas em grafos não direcionados
    for (Aresta* a : noOrigem->arestas) {
        if (a->id_no_alvo == destino_id) {
            return;
        }
    }

    Aresta* aresta = new Aresta();
    aresta->id_no_alvo = destino_id;
    aresta->peso = pesoAresta;
    noOrigem->arestas.push_back(aresta);

    // Se o grafo não é direcionado, adiciona a aresta reversa
    if (!in_direcionado) {
        Aresta* aresta2 = new Aresta();
        aresta2->id_no_alvo = origem_id;
        aresta2->peso = pesoAresta;
        noDestino->arestas.push_back(aresta2);
    }
}

// DFS auxiliar para fecho transitivo direto
void Grafo::dfs_fecho_direto(char u_id, std::set<char>& visitado) {
    visitado.insert(u_id);
    No* u_node = getNo(u_id);
    if (!u_node) return;

    for (Aresta* aresta : u_node->arestas) {
        if (visitado.find(aresta->id_no_alvo) == visitado.end()) {
            dfs_fecho_direto(aresta->id_no_alvo, visitado);
        }
    }
}

// Fecho transitivo direto (DFS)
vector<char> Grafo::fecho_transitivo_direto(char id_no) {
    if (!in_direcionado) {
        cout << "AVISO: Fecho transitivo direto é mais relevante para grafos direcionados." << endl;
    }
    No* start_node = getNo(id_no);
    if (start_node == nullptr) {
        cout << "ERRO: No de partida nao encontrado." << endl;
        return {};
    }

    set<char> visitado;
    dfs_fecho_direto(id_no, visitado);

    vector<char> resultado(visitado.begin(), visitado.end());
    // Remove o nó de partida do resultado, se presente, pois o fecho transitivo geralmente não o inclui
    resultado.erase(remove(resultado.begin(), resultado.end(), id_no), resultado.end());
    return resultado;
}

// Fecho transitivo indireto (construção de grafo reverso e DFS)
vector<char> Grafo::fecho_transitivo_indireto(char id_no) {
    if (!in_direcionado) {
        cout << "AVISO: Fecho transitivo indireto é mais relevante para grafos direcionados." << endl;
    }
    No* start_node = getNo(id_no);
    if (start_node == nullptr) {
        cout << "ERRO: No de partida nao encontrado." << endl;
        return {};
    }

    // Constrói o grafo reverso
    map<char, vector<char>> grafo_reverso;
    for (No* no : lista_adj) {
        grafo_reverso[no->id] = {}; // Garante que todos os nós estejam no mapa
    }
    for (No* no_origem : lista_adj) {
        for (Aresta* aresta : no_origem->arestas) {
            grafo_reverso[aresta->id_no_alvo].push_back(no_origem->id);
        }
    }

    set<char> visitado;
    queue<char> q;

    q.push(id_no);
    visitado.insert(id_no);

    while (!q.empty()) {
        char u = q.front();
        q.pop();

        // Percorre os "predecessores" no grafo original (sucessores no grafo reverso)
        for (char v : grafo_reverso[u]) {
            if (visitado.find(v) == visitado.end()) {
                visitado.insert(v);
                q.push(v);
            }
        }
    }

    vector<char> resultado(visitado.begin(), visitado.end());
    // Remove o nó de partida do resultado
    resultado.erase(remove(resultado.begin(), resultado.end(), id_no), resultado.end());
    return resultado;
}

// Dijkstra: caminho mínimo entre dois vértices 
vector<char> Grafo::caminho_minimo_dijkstra(char id_no_a, char id_no_b) {
    if (!in_ponderado_aresta) {
        cout << "ERRO: Dijkstra requer um grafo ponderado nas arestas." << endl;
        return {};
    }
    if (getNo(id_no_a) == nullptr || getNo(id_no_b) == nullptr) {
        cout << "ERRO: Um ou ambos os vertices nao existem no grafo." << endl;
        return {};
    }
    if (id_no_a == id_no_b) {
        return {id_no_a};
    }

    map<char, int> dist;
    map<char, char> prev;
    set<char> visitado;

    // Inicializa distâncias com infinito e predecessores vazios
    for (No* no : lista_adj) {
        dist[no->id] = numeric_limits<int>::max();
    }
    dist[id_no_a] = 0;

    // Fila de prioridade: pair<distancia, id_no>
    // Usa greater para min-heap (menor distância no topo)
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
    pq.push({0, id_no_a});

    while (!pq.empty()) {
        int d = pq.top().first;
        char u = pq.top().second;
        pq.pop();

        if (visitado.count(u)) {
            continue;
        }
        visitado.insert(u);

        // Se o destino foi alcançado, podemos parar
        if (u == id_no_b) {
            break;
        }

        No* current_node = getNo(u);
        if (current_node == nullptr) continue; // Deve ser impossível se os IDs são válidos

        for (Aresta* aresta : current_node->arestas) {
            char v = aresta->id_no_alvo;
            int peso_aresta = aresta->peso;

            if (dist[u] != numeric_limits<int>::max() && dist[v] > dist[u] + peso_aresta) {
                dist[v] = dist[u] + peso_aresta;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // Reconstrói o caminho
    vector<char> path;
    if (dist[id_no_b] == numeric_limits<int>::max()) {
        return {}; // Não há caminho
    }

    char current = id_no_b;
    while (current != id_no_a) {
        path.push_back(current);
        if (prev.find(current) == prev.end()) { // Caminho incompleto (erro ou no desconectado)
            return {};
        }
        current = prev[current];
    }
    path.push_back(id_no_a);
    reverse(path.begin(), path.end());
    return path;
}

// Floyd-Warshall: caminho mínimo entre dois vértices 
vector<char> Grafo::caminho_minimo_floyd(char id_no_a, char id_no_b) {
    if (!in_ponderado_aresta) {
        cout << "ERRO: Floyd requer um grafo ponderado nas arestas." << endl;
        return {};
    }
    if (getNo(id_no_a) == nullptr || getNo(id_no_b) == nullptr) {
        cout << "ERRO: Um ou ambos os vertices nao existem no grafo." << endl;
        return {};
    }

    int n = lista_adj.size();
    if (n == 0) return {};

    map<char, int> id_to_idx;
    vector<char> idx_to_id(n);
    for (int i = 0; i < n; ++i) {
        id_to_idx[lista_adj[i]->id] = i;
        idx_to_id[i] = lista_adj[i]->id;
    }

    // Matrizes de distância e predecessor
    vector<vector<int>> dist(n, vector<int>(n, numeric_limits<int>::max()));
    vector<vector<int>> next(n, vector<int>(n, -1)); // Armazena o próximo vértice no caminho

    // Inicialização
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
        for (Aresta* aresta : lista_adj[i]->arestas) {
            int j = id_to_idx[aresta->id_no_alvo];
            dist[i][j] = aresta->peso;
            next[i][j] = j;
        }
    }

    // Algoritmo de Floyd-Warshall
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // Evita overflow se dist[i][k] ou dist[k][j] for max
                if (dist[i][k] != numeric_limits<int>::max() &&
                    dist[k][j] != numeric_limits<int>::max() &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // Reconstruir o caminho
    int u_idx = id_to_idx[id_no_a];
    int v_idx = id_to_idx[id_no_b];

    if (dist[u_idx][v_idx] == numeric_limits<int>::max()) {
        return {}; // Não há caminho
    }

    vector<char> path;
    path.push_back(id_no_a);
    while (u_idx != v_idx) {
        u_idx = next[u_idx][v_idx];
        if (u_idx == -1) { // Erro inesperado no next, ou caminho quebrado
            return {};
        }
        path.push_back(idx_to_id[u_idx]);
    }
    return path;
}


// Função auxiliar para DFS na árvore de caminhamento
void Grafo::dfs_arvore_caminhamento(char u_id, std::set<char>& visitado, Grafo* arvore_dfs, std::set<pair<char, char>>& arestas_arvore) {
    visitado.insert(u_id);
    arvore_dfs->insereNo(u_id); // Garante que o nó esteja na árvore

    No* u_node = getNo(u_id);
    if (!u_node) return;

    // Arestas devem ser adicionadas na ordem da DFS
    // Para garantir a ordem, podemos ordenar as arestas de adjacência por id do alvo
    vector<Aresta*> sorted_arestas = u_node->arestas;
    sort(sorted_arestas.begin(), sorted_arestas.end(), [](Aresta* a1, Aresta* a2) {
        return a1->id_no_alvo < a2->id_no_alvo;
    });

    for (Aresta* aresta : sorted_arestas) {
        char v_id = aresta->id_no_alvo;
        if (visitado.find(v_id) == visitado.end()) {
            arvore_dfs->insereNo(v_id);
            arvore_dfs->insereAresta(u_id, v_id, aresta->peso); // Adiciona a aresta à árvore
            dfs_arvore_caminhamento(v_id, visitado, arvore_dfs, arestas_arvore);
        }
    }
}

// Árvore de caminhamento em profundidade (DFS)
Grafo* Grafo::arvore_caminhamento_profundidade(char id_no) {
    No* start_node = getNo(id_no);
    if (start_node == nullptr) {
        cout << "ERRO: No de partida nao encontrado." << endl;
        return new Grafo(); // Retorna um grafo vazio
    }

    Grafo* arvore_dfs = new Grafo();
    arvore_dfs->in_direcionado = this->in_direcionado;
    arvore_dfs->in_ponderado_aresta = this->in_ponderado_aresta;
    arvore_dfs->in_ponderado_vertice = this->in_ponderado_vertice;

    set<char> visitado;
    set<pair<char, char>> arestas_arvore; // Arestas da árvore de DFS

    dfs_arvore_caminhamento(id_no, visitado, arvore_dfs, arestas_arvore);

    // O problema especifica "destacando as arestas de retorno" mas "Orientações extras.pdf" diz para não destacar
    // A implementação atual constrói apenas a árvore de DFS, sem arestas de retorno explícitas na saída.
    return arvore_dfs;
}


// Raio, diâmetro, centro e periferia
// Usa BFS para calcular excentricidade de cada nó
int Grafo::raio() {
    if (in_direcionado) {
        cout << "ERRO: Raio, diametro, centro e periferia sao definidos para grafos nao direcionados." << endl;
        return -1; // Valor de erro
    }
    if (!ehConexo()) {
        cout << "ERRO: O grafo nao e conexo. Raio nao e aplicavel." << endl;
        return -1;
    }

    int min_eccentricity = numeric_limits<int>::max();

    for (No* start_node : lista_adj) {
        map<char, int> dist;
        for (No* n : lista_adj) {
            dist[n->id] = numeric_limits<int>::max();
        }
        dist[start_node->id] = 0;

        queue<char> q;
        q.push(start_node->id);

        int max_dist_from_start_node = 0;

        while (!q.empty()) {
            char u_id = q.front();
            q.pop();

            No* u_node = getNo(u_id);
            if (!u_node) continue; // Deve ser impossível

            for (Aresta* aresta : u_node->arestas) {
                char v_id = aresta->id_no_alvo;
                int weight = aresta->peso;

                if (dist[v_id] > dist[u_id] + weight) {
                    dist[v_id] = dist[u_id] + weight;
                    q.push(v_id);
                }
            }
        }

        // Calcula a excentricidade para start_node (máxima distância para qualquer outro nó)
        for (No* target_node : lista_adj) {
            if (dist[target_node->id] == numeric_limits<int>::max()) {
                // Não alcançável, o grafo não é conexo ou há erro.
                // Como já verificamos conexidade, isso indica um problema.
                return -1;
            }
            if (dist[target_node->id] > max_dist_from_start_node) {
                max_dist_from_start_node = dist[target_node->id];
            }
        }
        min_eccentricity = min(min_eccentricity, max_dist_from_start_node);
    }
    return min_eccentricity;
}

int Grafo::diametro() {
    if (in_direcionado) {
        cout << "ERRO: Raio, diametro, centro e periferia sao definidos para grafos nao direcionados." << endl;
        return -1; // Valor de erro
    }
    if (!ehConexo()) {
        cout << "ERRO: O grafo nao e conexo. Diametro nao e aplicavel." << endl;
        return -1;
    }

    int max_eccentricity = 0; // O diâmetro é a maior excentricidade

    for (No* start_node : lista_adj) {
        map<char, int> dist;
        for (No* n : lista_adj) {
            dist[n->id] = numeric_limits<int>::max();
        }
        dist[start_node->id] = 0;

        queue<char> q;
        q.push(start_node->id);

        int current_eccentricity = 0;

        while (!q.empty()) {
            char u_id = q.front();
            q.pop();

            No* u_node = getNo(u_id);
            if (!u_node) continue;

            for (Aresta* aresta : u_node->arestas) {
                char v_id = aresta->id_no_alvo;
                int weight = aresta->peso;

                if (dist[v_id] > dist[u_id] + weight) {
                    dist[v_id] = dist[u_id] + weight;
                    q.push(v_id);
                }
            }
        }
        // Calcula a excentricidade para start_node
        for (No* target_node : lista_adj) {
            if (dist[target_node->id] == numeric_limits<int>::max()) {
                // Se o grafo é conexo (verificado no início), isso não deve acontecer
                return -1;
            }
            if (dist[target_node->id] > current_eccentricity) {
                current_eccentricity = dist[target_node->id];
            }
        }
        if (current_eccentricity > max_eccentricity) {
            max_eccentricity = current_eccentricity;
        }
    }
    return max_eccentricity;
}

vector<char> Grafo::centro() {
    if (in_direcionado) {
        cout << "ERRO: Raio, diametro, centro e periferia sao definidos para grafos nao direcionados." << endl;
        return {};
    }
    if (!ehConexo()) {
        cout << "ERRO: O grafo nao e conexo. Centro nao e aplicavel." << endl;
        return {};
    }

    int r = raio();
    vector<char> cent_nodes;

    for (No* start_node : lista_adj) {
        map<char, int> dist;
        for (No* n : lista_adj) {
            dist[n->id] = numeric_limits<int>::max();
        }
        dist[start_node->id] = 0;

        queue<char> q;
        q.push(start_node->id);

        int current_eccentricity = 0;

        while (!q.empty()) {
            char u_id = q.front();
            q.pop();

            No* u_node = getNo(u_id);
            if (!u_node) continue;

            for (Aresta* aresta : u_node->arestas) {
                char v_id = aresta->id_no_alvo;
                int weight = aresta->peso;

                if (dist[v_id] > dist[u_id] + weight) {
                    dist[v_id] = dist[u_id] + weight;
                    q.push(v_id);
                }
            }
        }

        // Calcula a excentricidade para start_node
        for (No* target_node : lista_adj) {
            if (dist[target_node->id] == numeric_limits<int>::max()) {
                // Se o grafo é conexo, isso não deve acontecer
                return {};
            }
            if (dist[target_node->id] > current_eccentricity) {
                current_eccentricity = dist[target_node->id];
            }
        }
        if (current_eccentricity == r) {
            cent_nodes.push_back(start_node->id);
        }
    }
    sort(cent_nodes.begin(), cent_nodes.end()); // Opcional: ordenar para saída consistente
    return cent_nodes;
}

vector<char> Grafo::periferia() {
    if (in_direcionado) {
        cout << "ERRO: Raio, diametro, centro e periferia sao definidos para grafos nao direcionados." << endl;
        return {};
    }
    if (!ehConexo()) {
        cout << "ERRO: O grafo nao e conexo. Periferia nao e aplicavel." << endl;
        return {};
    }

    int d = diametro();
    vector<char> perif_nodes;

    for (No* start_node : lista_adj) {
        map<char, int> dist;
        for (No* n : lista_adj) {
            dist[n->id] = numeric_limits<int>::max();
        }
        dist[start_node->id] = 0;

        queue<char> q;
        q.push(start_node->id);

        int current_eccentricity = 0;

        while (!q.empty()) {
            char u_id = q.front();
            q.pop();

            No* u_node = getNo(u_id);
            if (!u_node) continue;

            for (Aresta* aresta : u_node->arestas) {
                char v_id = aresta->id_no_alvo;
                int weight = aresta->peso;

                if (dist[v_id] > dist[u_id] + weight) {
                    dist[v_id] = dist[u_id] + weight;
                    q.push(v_id);
                }
            }
        }

        // Calcula a excentricidade para start_node
        for (No* target_node : lista_adj) {
            if (dist[target_node->id] == numeric_limits<int>::max()) {
                // Se o grafo é conexo, isso não deve acontecer
                return {};
            }
            if (dist[target_node->id] > current_eccentricity) {
                current_eccentricity = dist[target_node->id];
            }
        }
        if (current_eccentricity == d) {
            perif_nodes.push_back(start_node->id);
        }
    }
    sort(perif_nodes.begin(), perif_nodes.end()); // Opcional: ordenar para saída consistente
    return perif_nodes;
}

// Algoritmo de Prim para Árvore Geradora Mínima
Grafo* Grafo::arvore_geradora_minima_prim(vector<char> ids_nos) {
    if (in_direcionado) {
        cout << "ERRO: O algoritmo de Prim e aplicavel apenas a grafos nao direcionados." << endl;
        return new Grafo();
    }
    if (!in_ponderado_aresta) {
        cout << "ERRO: O algoritmo de Prim requer um grafo ponderado nas arestas." << endl;
        return new Grafo();
    }
    if (ids_nos.empty()) {
        cout << "ERRO: Subconjunto de vertices vazio." << endl;
        return new Grafo();
    }

    // Cria um subgrafo induzido pelos vértices em ids_nos
    Grafo* induced_subgraph = new Grafo();
    induced_subgraph->in_direcionado = this->in_direcionado;
    induced_subgraph->in_ponderado_aresta = this->in_ponderado_aresta;
    induced_subgraph->in_ponderado_vertice = this->in_ponderado_vertice;

    map<char, bool> present_in_subset;
    for (char id : ids_nos) {
        No* original_node = getNo(id);
        if (original_node) {
            induced_subgraph->insereNo(id, original_node->peso);
            present_in_subset[id] = true;
        } else {
            cout << "AVISO: Vertice " << id << " do subconjunto nao encontrado no grafo original." << endl;
        }
    }

    for (char id_u : ids_nos) {
        No* u_node = getNo(id_u);
        if (u_node) {
            for (Aresta* aresta : u_node->arestas) {
                char id_v = aresta->id_no_alvo;
                if (present_in_subset[id_v]) {
                    // Adiciona aresta apenas se ambos os nós estão no subconjunto e a aresta ainda não foi adicionada
                    induced_subgraph->insereAresta(id_u, id_v, aresta->peso);
                }
            }
        }
    }

    if (induced_subgraph->lista_adj.empty()) {
        cout << "ERRO: Subgrafo induzido vazio." << endl;
        delete induced_subgraph;
        return new Grafo();
    }

    // Verifica se o subgrafo induzido é conexo
    if (!induced_subgraph->ehConexo()) {
        cout << "ERRO: O subgrafo induzido nao e conexo, nao e possivel gerar uma AGM." << endl;
        delete induced_subgraph;
        return new Grafo();
    }

    Grafo* mst = new Grafo();
    mst->in_direcionado = false; // AGM é sempre não direcionada
    mst->in_ponderado_aresta = true;
    mst->in_ponderado_vertice = induced_subgraph->in_ponderado_vertice;

    map<char, int> key; // menor peso de aresta para conectar ao MST
    map<char, char> parent; // pai no MST
    map<char, bool> in_mst; // se o nó já está no MST

    // Inicializa
    for (No* node : induced_subgraph->lista_adj) {
        key[node->id] = numeric_limits<int>::max();
        parent[node->id] = '\0'; // Caractere nulo para indicar sem pai
        in_mst[node->id] = false;
        mst->insereNo(node->id, node->peso); // Adiciona todos os nós ao MST inicial
    }

    // Começa com o primeiro nó do subconjunto
    char start_id = ids_nos[0];
    key[start_id] = 0;

    // Fila de prioridade: {peso, id_no}
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
    pq.push({0, start_id});

    while (!pq.empty()) {
        char u_id = pq.top().second;
        pq.pop();

        if (in_mst[u_id]) {
            continue;
        }
        in_mst[u_id] = true;

        if (parent[u_id] != '\0') { // Se não for o nó inicial
            mst->insereAresta(parent[u_id], u_id, key[u_id]);
        }

        No* u_node = induced_subgraph->getNo(u_id);
        if (!u_node) continue;

        for (Aresta* aresta : u_node->arestas) {
            char v_id = aresta->id_no_alvo;
            int weight = aresta->peso;

            // Apenas considera nós que estão no subconjunto e ainda não estão no MST
            if (in_mst.count(v_id) && !in_mst[v_id] && weight < key[v_id]) {
                key[v_id] = weight;
                parent[v_id] = u_id;
                pq.push({key[v_id], v_id});
            }
        }
    }
    delete induced_subgraph;
    return mst;
}


// Estrutura para Disjoint Set Union (DSU)
struct DSU {
    map<char, char> parent;
    map<char, int> ranks; // Para otimização por rank

    DSU(const vector<char>& ids) {
        for (char id : ids) {
            parent[id] = id;
            ranks[id] = 0;
        }
    }

    char find(char i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(char i, char j) {
        char root_i = find(i);
        char root_j = find(j);
        if (root_i != root_j) {
            if (ranks[root_i] < ranks[root_j])
                parent[root_i] = root_j;
            else if (ranks[root_i] > ranks[root_j])
                parent[root_j] = root_i;
            else {
                parent[root_j] = root_i;
                ranks[root_i]++;
            }
        }
    }
};

// Algoritmo de Kruskal para Árvore Geradora Mínima 
Grafo* Grafo::arvore_geradora_minima_kruskal(vector<char> ids_nos) {
    if (in_direcionado) {
        cout << "ERRO: O algoritmo de Kruskal e aplicavel apenas a grafos nao direcionados." << endl;
        return new Grafo();
    }
    if (!in_ponderado_aresta) {
        cout << "ERRO: O algoritmo de Kruskal requer um grafo ponderado nas arestas." << endl;
        return new Grafo();
    }
    if (ids_nos.empty()) {
        cout << "ERRO: Subconjunto de vertices vazio." << endl;
        return new Grafo();
    }

    // Cria um subgrafo induzido pelos vértices em ids_nos
    Grafo* induced_subgraph = new Grafo();
    induced_subgraph->in_direcionado = this->in_direcionado;
    induced_subgraph->in_ponderado_aresta = this->in_ponderado_aresta;
    induced_subgraph->in_ponderado_vertice = this->in_ponderado_vertice;

    map<char, bool> present_in_subset;
    for (char id : ids_nos) {
        No* original_node = getNo(id);
        if (original_node) {
            induced_subgraph->insereNo(id, original_node->peso);
            present_in_subset[id] = true;
        } else {
            cout << "AVISO: Vertice " << id << " do subconjunto nao encontrado no grafo original." << endl;
        }
    }

    for (char id_u : ids_nos) {
        No* u_node = getNo(id_u);
        if (u_node) {
            for (Aresta* aresta : u_node->arestas) {
                char id_v = aresta->id_no_alvo;
                if (present_in_subset[id_v]) {
                    // Adiciona aresta apenas se ambos os nós estão no subconjunto e a aresta ainda não foi adicionada
                    induced_subgraph->insereAresta(id_u, id_v, aresta->peso);
                }
            }
        }
    }

    if (induced_subgraph->lista_adj.empty()) {
        cout << "ERRO: Subgrafo induzido vazio." << endl;
        delete induced_subgraph;
        return new Grafo();
    }

    // Verifica se o subgrafo induzido é conexo
    if (!induced_subgraph->ehConexo()) {
        cout << "ERRO: O subgrafo induzido nao e conexo, nao e possivel gerar uma AGM." << endl;
        delete induced_subgraph;
        return new Grafo();
    }

    vector<tuple<int, char, char>> arestas; // {peso, origem, destino}
    set<pair<char, char>> added_edges; // Para evitar adicionar arestas duplicadas (em grafos não direcionados)

    for (No* node : induced_subgraph->lista_adj) {
        for (Aresta* aresta : node->arestas) {
            char u = node->id;
            char v = aresta->id_no_alvo;
            int weight = aresta->peso;

            // Para grafos não direcionados, adiciona cada aresta uma vez
            if (u < v) { // Normaliza a ordem para evitar duplicatas
                arestas.emplace_back(weight, u, v);
            }
        }
    }

    sort(arestas.begin(), arestas.end()); // Ordena as arestas por peso

    DSU dsu(ids_nos);
    Grafo* mst = new Grafo();
    mst->in_direcionado = false; // AGM é sempre não direcionada
    mst->in_ponderado_aresta = true;
    mst->in_ponderado_vertice = induced_subgraph->in_ponderado_vertice;

    // Adiciona todos os nós ao MST inicialmente
    for (char id : ids_nos) {
        No* original_node = getNo(id);
        if (original_node) {
            mst->insereNo(id, original_node->peso);
        }
    }

    for (const auto& edge : arestas) {
        int weight = get<0>(edge);
        char u = get<1>(edge);
        char v = get<2>(edge);

        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            mst->insereAresta(u, v, weight);
        }
    }

    delete induced_subgraph;
    return mst;
}


// Verifica se o grafo é conexo (usando BFS a partir de um nó qualquer) 
bool Grafo::ehConexo() {
    if (lista_adj.empty()) return true; // Grafo vazio é considerado conexo

    set<char> visitado;
    queue<char> q;

    // Começa a BFS a partir do primeiro nó na lista de adjacência
    char start_node_id = lista_adj[0]->id;
    q.push(start_node_id);
    visitado.insert(start_node_id);

    int count_visited = 0;
    while (!q.empty()) {
        char u_id = q.front();
        q.pop();
        count_visited++;

        No* u_node = getNo(u_id);
        if (!u_node) continue; // Deve ser impossível

        for (Aresta* aresta : u_node->arestas) {
            if (visitado.find(aresta->id_no_alvo) == visitado.end()) {
                visitado.insert(aresta->id_no_alvo);
                q.push(aresta->id_no_alvo);
            }
        }
    }
    // Para grafos não direcionados, se todos os nós foram visitados, é conexo.
    // Para grafos direcionados, isso verifica apenas se o componente fortemente conectado do nó inicial é o grafo inteiro.
    // A definição de "conexidade" para Prim/Kruskal refere-se a grafos não direcionados.
    return count_visited == this->lista_adj.size();
}

// Retorna todas as arestas do grafo como pares (origem, destino)
std::vector<std::pair<char, char>> Grafo::getTodasArestas() const {
    std::vector<std::pair<char, char>> arestas;
    std::set<std::pair<char, char>> arestas_set; // Para evitar duplicatas em grafos não direcionados
    for (const No* no : lista_adj) {
        for (const Aresta* aresta : no->arestas) {
            char origem = no->id;
            char destino = aresta->id_no_alvo;
            if (!in_direcionado) {
                // Ordena o par para evitar duplicatas
                if (origem > destino) std::swap(origem, destino);
            }
            std::pair<char, char> par = {origem, destino};
            if (arestas_set.find(par) == arestas_set.end()) {
                arestas.push_back(par);
                arestas_set.insert(par);
            }
        }
    }
    return arestas;
}

// Retorna todas as arestas adjacentes a uma aresta (compartilham um vértice)
std::vector<std::pair<char, char>> Grafo::getArestasAdjacentes(const std::pair<char, char>& aresta) const {
    std::vector<std::pair<char, char>> adjacentes;
    char u = aresta.first;
    char v = aresta.second;
    auto todas = getTodasArestas();
    for (const auto& a : todas) {
        if (a == aresta) continue;
        if (a.first == u || a.second == u || a.first == v || a.second == v) {
            adjacentes.push_back(a);
        }
    }
    return adjacentes;
}

// Retorna o número total de arestas
int Grafo::getNumArestas() const {
    return getTodasArestas().size();
}

// Retorna o número total de vértices
int Grafo::getNumVertices() const {
    return ordem;
}