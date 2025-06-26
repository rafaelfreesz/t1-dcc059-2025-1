#include <iostream>
#include <iterator>
#include "Gerenciador.h"

using namespace std;
int main(int argc, char *argv[])
{
    if (argc == 0){
        cout << "Erro: Nenhum grafo especificado" << endl;
        exit(0);
    }
    if (argc > 2){
        cout << "Erro: Mais de um grafo ao mesmo tempo" << endl;
        exit(0);
    }

    
    cout << "argc: " << argc << endl
         << "argv: " << endl;
    for(int i = 0; i < argc; i++)
        cout << i << ": " << argv[i] <<endl;
    

    Grafo* grafo = new Grafo();

    Gerenciador::comandos(grafo);

    return 0;
}
