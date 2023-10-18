#include "simulador.h"

// Construtor
Simulador::Simulador(int num_frames, vector<int> references)
    : references(references), memory(num_frames),
      pagingFIFO(make_unique<FifoPaging>(memory)),
      pagingLRU(make_unique<LruPaging>(memory)),
      pagingOPT(make_unique<OptPaging>(memory, references)) {}

// Inicia simulação
void Simulador::start_simulation() {
    // Executa algoritmo para cada referencia
    for (int page : references) {
        // Referencia páginas
        pagingFIFO->refer(page);
        pagingLRU->refer(page);
        pagingOPT->refer(page);
    }
}

// Imprime resultados no terminal
void Simulador::print_terminal() {
    // Imprime quantidade de quadros e referencias
    cout << memory.getNumFrames() << " quadros" << endl;
    cout << references.size() -1 << " refs" << endl;
    // Imprime quantidade de falta de páginas algoritmos
    cout << "FIFO Page Faults: " << pagingFIFO->getPageFaultCount() << "\n";
    cout << "LRU Page Faults: " << pagingLRU->getPageFaultCount() << "\n";
    cout << "OPT Page Faults: " << pagingOPT->getPageFaultCount() << "\n";
}