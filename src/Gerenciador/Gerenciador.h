#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include <iostream>
#include "../Grafo/Grafo.h"
#include "../No/No.h"
#include "../Aresta/Aresta.h"

#include <algorithm>
#include <vector>
#include <string>

// Usando namespace std para conveniência, mas pode ser evitado em arquivos de cabeçalho maiores
using namespace std;

class Gerenciador {
public:
    // Exibe o menu de comandos e gerencia a interação do usuário 
    static void comandos(Grafo* grafo);

    // Solicita um ID de nó ao usuário
    static char get_id_entrada();

    // Solicita um subconjunto de IDs de nós ao usuário 
    static vector<char> get_conjunto_ids(Grafo* grafo, int tam);

    // Pergunta ao usuário se deseja salvar a saída em arquivo 
    static bool pergunta_imprimir_arquivo(string nome_arquivo);

    // Métodos auxiliares para impressão de resultados 
    static void imprimir_vector_char(const vector<char>& vec);
    static void imprimir_grafo(Grafo* grafo);
    static void imprimir_h_output(int raio, int diametro, const vector<char>& centro, const vector<char>& periferia);
    
    static int solicitarInteiro(string mensagem, int ordem);
};

#endif //GERENCIADOR_H