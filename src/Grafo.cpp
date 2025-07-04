#include "Grafo.h"
#include "No.h"
#include <cstdlib>
#include <set>
//#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
Grafo::Grafo()
{
    ordem = 0;
    in_direcionado = false;
    in_ponderado_aresta = false;
    in_ponderado_vertice = false;
    lista_adj = vector<No *>();
}
// Novo construtor com nome do arquivo
Grafo::Grafo(const std::string &nome_arquivo) : Grafo()
{                                 // chama o construtor padrão
    carregaArquivo(nome_arquivo); // carrega o grafo ao criar o objeto
}
// recebe string com o nome do grafo do comando de execução.
//./execGrupoX nome_do_txt <---string recebida
void Grafo::carregaArquivo(const string &grafo)
{

    // filesystem::path base_path = "../t1-dcc059/instancias/";
    // filesystem::path full_path = base_path / grafo;

    string caminho = "../instancias/" + grafo;
    cout << "Tentando abrir arquivo em: " << caminho << endl;

    ifstream arquivo(caminho);
    string line;
    size_t location;

    if (!arquivo.is_open())
    {
        cerr << "Erro ao abrir arquivo: " << grafo << endl;
        exit(1);
    }
    // linha zero. [ex: (0 0 0), (0 1 1)]
    getline(arquivo, line);
    // trata excelçoes na quantidade de argumentos da linha
    if (line.length() != 5)
    {
        cout << line.length() << endl;
        cout << "Erro: formato inválido da lista de adjacencia. linha 0" << endl;
        exit(0);
    }
    set_direcionado(line.at(0) == '1');       // define se o grafo é orientado
    set_ponderado_aresta(line.at(2) == '1');  // define se o grafo é ponderado nas arestas
    set_ponderado_vertice(line.at(4) == '1'); // define se o grafo é ponderado nos vertices

    // linha um. ordem do grafo
    getline(arquivo, line);
    // trata exceções na quantidade de argumentos da linha
    if (line.length() != 1)
    {
        cout << "Erro: grafo deve possuir apenas UM(1) valor para a ordem." << endl;
        exit(0);
    }
    ordem = stoi(line); // converte string inteira pra int

    vector<No *> v = get_vertices();
    if (get_ponderado_vertice() == true)
    {
        for (int i = 0; i < ordem; ++i)
        {
            getline(arquivo, line);

            if (!line.empty())
            {
                char nome;
                int peso;
                std::istringstream iss(line);
                iss >> nome >> peso;

                No *p = new No(nome, peso);
                lista_adj.push_back(p);
            }
        }
        cout << endl;
        // set_vertices(v);
    }
    else
    {
        for (int i = 0; i < ordem; ++i)
        {
            getline(arquivo, line);
            if (!line.empty())
            {
                No *p = new No(line.at(0));
                lista_adj.push_back(p);
            }
        }
    }

    // Read graph properties
    // arquivo >> in_direcionado >> in_ponderado_aresta >> in_ponderado_vertice;
    // arquivo >> ordem;

    // Read vertices
    while (getline(arquivo, line))
    {
        if (line.empty())
            continue;
        istringstream iss(line);
        char origem_id, destino_id;
        int peso = 1;

        if (in_ponderado_aresta)
        {
            iss >> origem_id >> destino_id >> peso;
        }
        else
        {
            iss >> origem_id >> destino_id;
        }

        No *origem = nullptr;
        No *destino = nullptr;

        for (No *no : lista_adj)
        {
            if (no->get_id() == origem_id)
                origem = no;
            if (no->get_id() == destino_id)
                destino = no;
        }

        if (origem && destino)
        {
            origem->add_vizinho(destino);
            origem->add_aresta(destino_id, peso);


            if (!in_direcionado)
            {
                destino->add_vizinho(origem);
                destino->add_aresta(origem_id, peso);

            }
        }
    }

    arquivo.close();
}
// cout << "Grafo carregado com sucesso de: " << grafo << endl;


void Grafo::imprimeInfo() const
{
    cout << "----- Informações do Grafo -----" << endl;
    cout << "Ordem: " << ordem << endl;
    cout << "Direcionado: " << (in_direcionado ? "Sim" : "Não") << endl;
    cout << "Ponderado nas Arestas: " << (in_ponderado_aresta ? "Sim" : "Não") << endl;
    cout << "Ponderado nos Vértices: " << (in_ponderado_vertice ? "Sim" : "Não") << endl;

    cout << "\nVértices:" << endl;
    for (const auto &no : lista_adj )
    {
        cout << "- " << no->get_id();
        if (get_ponderado_vertice())
        {
            cout << " (peso: " << no->get_peso() << ")";
        }
        cout << endl;
    }

    cout << "---------------------------------" << endl;
}

void Grafo::aux_dfs(No *no, set<char> &visitado)
{
    if (visitado.find(no->get_id()) == visitado.end())
    {
        visitado.insert(no->get_id());
        for (No *vizinho : no->get_vizinhos())
        {
            aux_dfs(vizinho, visitado);
        }
    }
}

Grafo::~Grafo()
{
}

vector<char> Grafo::fecho_transitivo_indireto(char id_no) {
    set<char> fecho;
    for (No* no : lista_adj) {
        set<char> visitado;
        aux_dfs(no, visitado);
        if (visitado.find(id_no) != visitado.end()) {
            fecho.insert(no->get_id());
        }
    }
    fecho.erase(id_no); // opcional: remover o próprio nó
    return vector<char>(fecho.begin(), fecho.end());
}

vector<char> Grafo::fecho_transitivo_indireto(char id_no)
{
    cout << "Metodo nao implementado" << endl;
    return {};
}

vector<char> Grafo::caminho_minimo_dijkstra(char id_no_a, char id_no_b)
{
    cout << "Metodo nao implementado" << endl;
    return {};
}

vector<char> Grafo::caminho_minimo_floyd(char id_no, char id_no_b)
{
    cout << "Metodo nao implementado" << endl;
    return {};
}

Grafo *Grafo::arvore_geradora_minima_prim(vector<char> ids_nos)
{
    cout << "Metodo nao implementado" << endl;
    return nullptr;
}

Grafo *Grafo::arvore_geradora_minima_kruskal(vector<char> ids_nos)
{
    cout << "Metodo nao implementado" << endl;
    return nullptr;
}

Grafo *Grafo::arvore_caminhamento_profundidade(char id_no)
{
    cout << "Metodo nao implementado" << endl;
    return nullptr;
}

int Grafo::raio()
{
    cout << "Metodo nao implementado" << endl;
    return 0;
}

int Grafo::diametro()
{
    cout << "Metodo nao implementado" << endl;
    return 0;
}

vector<char> Grafo::centro()
{
    cout << "Metodo nao implementado" << endl;
    return {};
}

vector<char> Grafo::periferia()
{
    cout << "Metodo nao implementado" << endl;
    return {};
}

vector<char> Grafo::vertices_de_articulacao()
{
    cout << "Metodo nao implementado" << endl;
    return {};
}
