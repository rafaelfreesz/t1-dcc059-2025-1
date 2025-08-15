#include <iostream>
#include "Gerenciador/Gerenciador.h"

int main(int argc, char *argv[])
{
    std::cout << std::endl << "--------------------------------------------------------------------------------------------------" << std::endl;

    // Verifica se o nome do arquivo foi passado como argumento [cite: 14]
    if (argc != 2) {
        std::cout << "ERRO: O programa deve ser executado como: ./execGrupoX <arquivo_entrada>" << std::endl; 
    }

    // Cria o grafo a partir do arquivo de entrada [cite: 7]
    Grafo* grafo = new Grafo(argv[1]);

    // Inicia o menu de comandos 
    Gerenciador::comandos(grafo);

    // Libera a memória alocada
    delete grafo;

    return 0;
}