#include "FIFO.h"
#include "memory.h"
#include <algorithm>
#include <vector>

// Construtor com parâmetro
FifoPaging::FifoPaging(Memory memory) : AbstractPaging(memory) {}

// Submissão de uma página para análise
void FifoPaging::refer(int num) {
    // Verifica se referência foi encontrada no vetor de páginas
    if (!memory.find(num)) {
        // Mais uma falta de página
        ++pageFault;
        // Verifica se o vetor de páginas está cheio
        if (memory.isFull()) {
            // Deleta página do início
            memory.erasePageBegin();
        }
        // Adciciona página no fim
        memory.addPageEnd(num);
    }
}
