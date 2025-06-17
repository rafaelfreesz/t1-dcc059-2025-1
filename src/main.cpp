#include <iostream>
#include "Gerenciador.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_entrada>" << std::endl;
        return 1;
    }

    Grafo* grafo = nullptr;
    try {
        // Agora o carregamento é feito pelo Gerenciador
        grafo = Gerenciador::carregarGrafoDoArquivo(argv[1]);
        std::cout << "Grafo carregado com sucesso!" << std::endl;
        std::cout << "Ordem: " << grafo->ordem << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        if (grafo) delete grafo;
        return 1;
    }

    Gerenciador::comandos(grafo);
    delete grafo;
    return 0;
}