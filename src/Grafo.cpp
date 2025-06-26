#include "Grafo.h"
#include "No.h"
#include <cstdlib>
#include <set>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
Grafo::Grafo() {
    ordem = 0;
    in_direcionado = false;
    in_ponderado_aresta = false;
    in_ponderado_vertice = false;
    lista_adj = vector<No*>();
}
// Novo construtor com nome do arquivo
Grafo::Grafo(const std::string& nome_arquivo) : Grafo() { // chama o construtor padrão
    carregaArquivo(nome_arquivo); // carrega o grafo ao criar o objeto
}
//recebe string com o nome do grafo do comando de execução.
//./execGrupoX nome_do_txt <---string recebida
void Grafo::carregaArquivo(const string& grafo){
    
    // filesystem::path base_path = "../t1-dcc059/instancias/";
    // filesystem::path full_path = base_path / grafo;


    string caminho = "../instancias/" + grafo;
    cout << "Tentando abrir arquivo em: " << caminho << endl;
    
    ifstream arquivo(caminho);
    string line;
    size_t location;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir arquivo: " << grafo << endl;
        exit(1);
    }
    //linha zero. [ex: (0 0 0), (0 1 1)]
    getline(arquivo, line);
    //trata excelçoes na quantidade de argumentos da linha
    if (line.length() != 5){
        cout << line.length() << endl;
        cout << "Erro: formato inválido da lista de adjacencia. linha 0" << endl;
        exit(0);
    }
    set_direcionado(line.at(0)); //define se o grafo é orientado
    set_ponderado_aresta(line.at(1)); //define se o grafo é ponderado nas arestas
    set_ponderado_vertice(line.at(2)); //define se o grafo é ponderado nos vertices

    //linha um. ordem do grafo
    getline(arquivo, line);
    //trata exceções na quantidade de argumentos da linha
    if (line.length() != 1){
        cout << "Erro: grafo deve possuir apenas UM(1) valor para a ordem." << endl;
        exit(0);
    }
    set_ordem(line.at(0));

    vector<No*> v = get_vertices();
    if (get_ponderado_vertice() == true){
        for (int i = 0; i < ordem; ++i) {
            getline(arquivo, line);

            if (!line.empty()){
                char nome;
                int peso;
                std::istringstream iss(line);
                iss >> nome >> peso;
                
                No *p = new No(nome, peso);
                this->vertices.push_back(p);
            }
        }
        cout << endl;
        // set_vertices(v);
    } else {
        for (int i = 0; i < ordem; ++i){
            getline(arquivo, line);
            if (!line.empty()){
                No *p = new No(line.at(0));
                this->vertices.push_back(p);
            }
        }
            
    }
    

    // Read graph properties
    // arquivo >> in_direcionado >> in_ponderado_aresta >> in_ponderado_vertice;
    // arquivo >> ordem;

    // Read vertices
    // for (int i = 0; i < ordem; ++i) {
    //     char id;
    //     int peso = 0;
        
    //     if (in_ponderado_vertice) {
    //         arquivo >> id >> peso;
    //     } else {
    //         arquivo >> id;
    //     }
        
    //     No* novo_no = new No(id, peso);
    //     lista_adj.push_back(novo_no);
    // }

    // // Read edges
    // string linha;
    // while (getline(arquivo, linha)) {
    //     if (linha.empty()) continue;
        
    //     istringstream iss(linha);
    //     char id_a, id_b;
    //     int peso = 1;
        
    //     if (in_ponderado_aresta) {
    //         iss >> id_a >> id_b >> peso;
    //     } else {
    //         iss >> id_a >> id_b;
    //     }
        
    //     // Find nodes and create edge
    //     No* origem = nullptr;
    //     No* destino = nullptr;
        
    //     for (No* no : lista_adj) {
    //         if (no->id == id_a) origem = no;
    //         if (no->id == id_b) destino = no;
    //     }
        
    //     if (origem && destino) {
    //         origem->vizinhos.push_back(destino);
    //         if (!in_direcionado) {
    //             destino->vizinhos.push_back(origem);
    //         }
    //     }
    // }

    // arquivo.close();
    // cout << "Grafo carregado com sucesso de: " << grafo << endl;
}

void Grafo::imprimeInfo() const {
    cout << "----- Informações do Grafo -----" << endl;
    cout << "Ordem: " << ordem << endl;
    cout << "Direcionado: " << (in_direcionado ? "Sim" : "Não") << endl;
    cout << "Ponderado nas Arestas: " << (in_ponderado_aresta ? "Sim" : "Não") << endl;
    cout << "Ponderado nos Vértices: " << (in_ponderado_vertice ? "Sim" : "Não") << endl;

    cout << "\nVértices:" << endl;
    for (const auto& no : vertices) {
        cout << "- " << no->get_id();
        if (get_ponderado_vertice()) {
            cout << " (peso: " << no->get_peso() << ")";
        }        
        cout << endl;
    }

    cout << "---------------------------------" << endl;
}

void Grafo::aux_dfs(No* no, set<char>& visitado) {
    if (visitado.find(no->get_id()) == visitado.end()) {
        visitado.insert(no->get_id());
        for (No* vizinho : no->get_vizinhos()) {
            aux_dfs(vizinho, visitado);
        }
    }
}

Grafo::~Grafo() {
}

vector<char> Grafo::fecho_transitivo_direto(int id_no) {
    No* origem = nullptr;
    for (No* no : lista_adj) {
        if (no->get_id() == id_no) {
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

    // cout<<"Metodo nao implementado"<<endl;
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
