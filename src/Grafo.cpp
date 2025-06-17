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


//MÉTODO NOVO (TESTE)


void Grafo::carregarArquivo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        throw runtime_error("Erro ao abrir: " + nomeArquivo);
    }

    // Essa vai ser pra ler dados da linha 1 
    if (!(arquivo >> direcionado >> ponderadoVertices >> ponderadoArestas)) {
        throw runtime_error("Formato inválido na linha 1");
    }

    // Essa vai ser pra ler número de vértices (linha 2)
    int numVertices;
    if (!(arquivo >> numVertices) || numVertices <= 0) {
        throw runtime_error("Número de vértices inválido");
    }

    // Essa vai ser pra ler info dos vértices
    char id;
    float peso;
    for (int i = 0; i < numVertices; i++) {
        if (ponderadoVertices) {
            if (!(arquivo >> id >> peso)) {
                throw runtime_error("Erro ao ler vértice " + to_string(i+1));
            }
            pesosVertices[id] = peso;
        } else {
            if (!(arquivo >> id)) {
                throw runtime_error("Erro ao ler vértice " + to_string(i+1));
            }
        }
        lista_adj.push_back(new No(id, peso));
    }

    // Essa vai ser pra ler arestas
    string linha;
    getline(arquivo, linha); // Consumir quebra de linha residual
    
    char origem, destino;
    float pesoAresta = 1.0f; // Default para grafos não ponderados
    
    while (getline(arquivo, linha)) {
        if (linha.empty()) continue;
        
        istringstream iss(linha);
        if (!(iss >> origem >> destino)) {
            throw runtime_error("Formato inválido de aresta: " + linha);
        }
        
        if (ponderadoArestas && !(iss >> pesoAresta)) {
            throw runtime_error("Peso faltando em aresta: " + linha);
        }

        // Essa vai ser pra Encontrar nó de origem na lista
        auto it = find_if(lista_adj.begin(), lista_adj.end(), 
            [&](No* no) { return no->getID() == origem; });
        
        if (it == lista_adj.end()) {
            throw runtime_error("Vértice de origem não encontrado: " + string(1, origem));
        }
        
        // Essa vai ser pra Adicionar aresta
        (*it)->adicionarAresta(new Aresta(destino, pesoAresta));
        
        // Essa vai ser pra Se não for direcionado, adicionar aresta inversa
        if (!direcionado) {
            auto it_dest = find_if(lista_adj.begin(), lista_adj.end(),
                [&](No* no) { return no->getID() == destino; });
            
            if (it_dest == lista_adj.end()) {
                throw runtime_error("Vértice de destino não encontrado: " + string(1, destino));
            }
            
            (*it_dest)->adicionarAresta(new Aresta(origem, pesoAresta));
        }
    }
}
