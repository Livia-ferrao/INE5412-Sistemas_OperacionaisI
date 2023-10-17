#include "simulador.h"
#include "FIFO.h" // Certifique-se de incluir os cabeçalhos corretos para suas classes de paginação
#include "LRU.h"
#include "OPT.h"

Simulador::Simulador(int num_frames, vector<int> references)
    : num_frames(num_frames), references(references), memory(num_frames),
      pagingFIFO(make_unique<FifoPaging>(memory)),
      pagingLRU(make_unique<LruPaging>(memory)),
      pagingOPT(make_unique<OptPaging>(memory, references)) {}

void Simulador::start_simulation() {
    for (int page : references) {
        pagingFIFO->refer(page);
        pagingLRU->refer(page);
        pagingOPT->refer(page);
    }
}

void Simulador::print_terminal() {
    cout << num_frames << " quadros" << endl;
    cout << references.size() -1 << " refs" << endl;

    cout << "FIFO Page Faults: " << pagingFIFO->getPageFaultCount() << "\n";
    cout << "LRU Page Faults: " << pagingLRU->getPageFaultCount() << "\n";
    cout << "OPT Page Faults: " << pagingOPT->getPageFaultCount() << "\n";
}