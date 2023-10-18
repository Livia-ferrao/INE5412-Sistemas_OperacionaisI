#include <iostream>
#include <memory>
#include <vector>
#include "abstract_paging.h"
#include "simulador.h"
#include "memory.h"
#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Leitura da entrada
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <num_frames>" << endl;
        return 1;
    }
    // Número de frames da memória RAM
    int num_frames = stoi(argv[1]);
    // Vetor de referências
    vector<int> references;
    // Cada linha do arquivo uma página
    int page;
    // Vetor recebe as páginas
    while (!feof(stdin))
    {
        scanf("%d",&page);
        references.push_back(page);
    }

    // Construtor
    Simulador simulador(num_frames, references);
    // Iniciar a simulação
    simulador.start_simulation();
    // Imprimir resultados
    simulador.print_terminal();
}