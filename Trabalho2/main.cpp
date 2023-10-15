#include <iostream>
#include <memory>
#include <vector>
#include "abstract_paging.h"
#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"
#include "memory.h"
#include "simulador.h"
#include <chrono>

using namespace std;

int main(int argc, char *argv[]) {
    auto start_time = std::chrono::high_resolution_clock::now();

    // Leitura da entrada
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <num_frames>" << endl;
        return 1;
    }
    // Número de frames da memória RAM
    int num_frames = stoi(argv[1]);
    // Vetor de páginas
    vector<int> references;
    // Cada linha do arquivo uma página
    int page;
    // Vetor recebe as páginas
    while (!feof(stdin))
    {
        scanf("%d",&page);
        references.push_back(page);
    }

    // Simulador simulador(num_frames, references);
    
    // // Iniciar a simulação
    // simulador.start_simulation();

    // // Imprimir resultados
    // simulador.print_terminal();

    // Ponteiro para o algoritmo de substituição de página
    std::unique_ptr<AbstractPaging> pagingFIFO;
    std::unique_ptr<AbstractPaging> pagingLRU;
    std::unique_ptr<AbstractPaging> pagingOPT;
    Memory memory(num_frames);

     // FIFO, LRU e OPT
    pagingFIFO = std::unique_ptr<AbstractPaging>(new FifoPaging(memory));
    pagingLRU = std::unique_ptr<AbstractPaging>(new LruPaging(memory));
    pagingOPT = std::unique_ptr<AbstractPaging>(new OptPaging(memory, references));

    for(int page: references ){
        pagingFIFO->refer(page);
        pagingLRU->refer(page);
        pagingOPT->refer(page);
    }

    // Método print 
    cout << num_frames << " quadros" << endl;
    cout << references.size() -1 << " refs" << endl;

     // Quantidade de faltas de páginas
    std::cout << "FIFO: " << pagingFIFO->getPageFaultCount() << std::endl;
    std::cout << "LRU: " << pagingLRU->getPageFaultCount() << std::endl;
    std::cout << "OPT: " << pagingOPT->getPageFaultCount() << std::endl;

    // Fim da contagem de tempo
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calcular a duração em milissegundos
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Tempo de execução: " << duration.count() << " ms" << std::endl;

 
}