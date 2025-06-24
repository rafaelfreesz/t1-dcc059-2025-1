#include "Grafo.h"
#include <set>
#include <filesystem>
#include <fstream>
#include <sstream>
using namespace std;
Grafo::Grafo() {
    ordem = 0;
    in_direcionado = false;
    in_ponderado_aresta = false;
    in_ponderado_vertice = false;
    lista_adj = vector<No*>();
}

void Grafo::carregaArquivo(const string& grafo){
    
    filesystem::path base_path = "/home/gabhriel/faculdade/t1-dcc059/instancias/";
    filesystem::path full_path = base_path / grafo;


    ifstream arquivo(full_path);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir arquivo: " << full_path << endl;
        return;
    }

    // Read graph properties
    arquivo >> in_direcionado >> in_ponderado_aresta >> in_ponderado_vertice;
    arquivo >> ordem;

    // Read vertices
    for (int i = 0; i < ordem; ++i) {
        char id;
        int peso = 0;
        
        if (in_ponderado_vertice) {
            arquivo >> id >> peso;
        } else {
            arquivo >> id;
        }
        
        No* novo_no = new No(id, peso);
        lista_adj.push_back(novo_no);
    }

    // Read edges
    string linha;
    while (getline(arquivo, linha)) {
        if (linha.empty()) continue;
        
        istringstream iss(linha);
        char id_a, id_b;
        int peso = 1;
        
        if (in_ponderado_aresta) {
            iss >> id_a >> id_b >> peso;
        } else {
            iss >> id_a >> id_b;
        }
        
        // Find nodes and create edge
        No* origem = nullptr;
        No* destino = nullptr;
        
        for (No* no : lista_adj) {
            if (no->id == id_a) origem = no;
            if (no->id == id_b) destino = no;
        }
        
        if (origem && destino) {
            origem->vizinhos.push_back(destino);
            if (!in_direcionado) {
                destino->vizinhos.push_back(origem);
            }
        }
    }

    arquivo.close();
    cout << "Grafo carregado com sucesso de: " << full_path << endl;
}


void Grafo::aux_dfs(No* no, set<char>& visitado) {
    if (visitado.find(no->id) == visitado.end()) {
        visitado.insert(no->id);
        for (No* vizinho : no->vizinhos) {
            aux_dfs(vizinho, visitado);
        }
    }
}

Grafo::~Grafo() {
}

vector<char> Grafo::fecho_transitivo_direto(int id_no) {
    No* origem = nullptr;
    for (No* no : lista_adj) {
        if (no->id == id_no) {
            origem = no;
            break;
        }
    }
    if (origem == nullptr) {
        cout << "No com id " << id_no << " nao encontrado." << endl;
        return {};
    }
    set<char> visitado;
    aux_dfs(origem, visitado);
    vector<char> resultado(visitado.begin(), visitado.end());
    return resultado; //talvez esteja certo, nao sei >>vale rever<<

    cout<<"Metodo nao implementado"<<endl;
}

vector<char> Grafo::fecho_transitivo_indireto(int id_no) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::caminho_minimo_dijkstra(int id_no_a, int id_no_b) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
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
