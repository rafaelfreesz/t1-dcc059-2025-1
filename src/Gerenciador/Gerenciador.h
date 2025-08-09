#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include <iostream>
#include "../Grafo/Grafo.h"
#include "../No/No.h"
#include "../Aresta/Aresta.h"

#include <algorithm>
#include <vector>
#include <string>



class Gerenciador {
public:
    static void comandos(Grafo* grafo);
    static char get_id_entrada();
    static std::vector<char> get_conjunto_ids(Grafo* grafo, int tam);
    static bool pergunta_imprimir_arquivo(std::string nome_arquivo);
    static void imprimir_vector_char(const std::vector<char>& vec);
    static void imprimir_grafo(Grafo* grafo);
    static void imprimir_h_output(int raio, int diametro, const std::vector<char>& centro, const std::vector<char>& periferia);
    static int solicitarInteiro(std::string mensagem, int ordem);
};

#endif //GERENCIADOR_H