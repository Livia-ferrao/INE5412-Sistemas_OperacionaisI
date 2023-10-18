#include "LRU.h"
#include "memory.h"
#include <algorithm>
#include <vector>

// Construtor com parâmetro
LruPaging::LruPaging(Memory memory) : AbstractPaging(memory) {}

// Submissão de uma página para análise
void LruPaging::refer(int num) {
    // Verifica se referência foi encontrada no vetor de páginas
    if (!memory.find(num)) {
        // Mais uma falta de página
        ++pageFault;
        // Verifica se a memória está cheia 
        if(memory.isFull()) {
            // Deleta página do início
            memory.erasePageBegin();
        }
        // Adiciona página no final
        memory.addPageEnd(num);
    } else {
        // Deleta página pelo número
        memory.erasePage(num);
        // Adiciona página no final
        memory.addPageEnd(num);
    }
}