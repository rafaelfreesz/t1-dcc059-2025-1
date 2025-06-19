#include "Gerenciador.h"

int main(int argc, char *argv[])
{
    cout << endl << "--------------------------------------------------------------------------------------------------"<< endl;

    // Verifica se o nome do arquivo foi passado como argumento
    if (argc != 2) {
        cout << "ERRO: O programa deve ser executado como: ./execGrupoX <arquivo_entrada>" << endl;
        return 1;
    }

    // Cria o grafo a partir do arquivo de entrada
    Grafo* grafo = new Grafo(argv[1]);

    // Inicia o menu de comandos
    Gerenciador::comandos(grafo);

    // Libera a memória alocada
    delete grafo;

    return 0;
}