#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include <iostream>
#include "Grafo.h"
#include <algorithm>

using namespace std;
class Gerenciador {
    public:
        static void comandos(Grafo* grafo);
        static Grafo* carregarGrafoDoArquivo(const std::string& nomeArquivo); //MÉTODO NOVO
        static char get_id_entrada();
        static std::vector<char> get_conjunto_ids(Grafo *grafo, int tam);
        static bool pergunta_imprimir_arquivo(std::string nome_arquivo);
    };


#endif //GERENCIADOR_H
