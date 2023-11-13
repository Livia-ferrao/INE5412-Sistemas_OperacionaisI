#ifndef SIMULADOR_H
#define SIMULADOR_H
#include <vector>
#include <iostream>
#include <memory>
#include "abstract_paging.h"
#include "memory.h"
#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"

class Simulador{
public:
    // Construtor
    Simulador(int num_frames, std::vector<int> references);
    // Inicia simulação
    void start_simulation();
    // Imprime resultado padrão no terminal
    void print_terminal();
private:
    // Vetor de referencias
    std::vector<int> references;
    // Memória
    Memory memory;
    // Ponteiro para algoritmo FIFO
    std::unique_ptr<AbstractPaging> pagingFIFO;
    // Ponteiro para algoritmo LRU
    std::unique_ptr<AbstractPaging> pagingLRU;
    // Ponteiro para algoritmo OPT
    std::unique_ptr<AbstractPaging> pagingOPT;
};

#endif // SIMULADOR_H
