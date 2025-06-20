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

    // Novo: Funções para cálculo das medidas
    struct MedidasGrafo {
        double raio;
        double diametro;
        std::vector<char> centro;
        std::vector<char> periferia;
    };
    
    static std::unordered_map<char, double> calcularDistanciasMinimas(Grafo* grafo, char origem);
    static std::unordered_map<char, double> calcularExcentricidades(Grafo* grafo);
    static MedidasGrafo calcularMedidas(Grafo* grafo);
    };


#endif //GERENCIADOR_H
