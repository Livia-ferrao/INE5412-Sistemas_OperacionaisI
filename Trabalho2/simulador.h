#ifndef SIMULADOR_H
#define SIMULADOR_H
#include <vector>
#include <iostream>
#include <memory>
#include "memory.h"
#include "abstract_paging.h"

class Simulador{
public:
    Simulador(int num_frames, std::vector<int> references);
    void start_simulation();
    void print_terminal();
private:
    std::vector<int> references;
    int num_frames;
    Memory memory;
    std::unique_ptr<AbstractPaging> pagingFIFO;
    std::unique_ptr<AbstractPaging> pagingLRU;
    std::unique_ptr<AbstractPaging> pagingOPT;
};

#endif // SIMULADOR_H
