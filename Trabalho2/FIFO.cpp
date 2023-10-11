// #include "FIFO.h"
// #include <algorithm>

// // Construtor com parâmetro
// FifoPaging::FifoPaging(int pageCount) : AbstractPaging(pageCount) {}

// // Submissão de uma página para análise
// void FifoPaging::refer(int page) {
//     if (std::find(mPages.begin(), mPages.end(), page) == mPages.end()) {
//         ++mPageFault;
//         if ((long)mPages.size() == (long)mPageCount) {
//             mPages.pop_front();
//         }
//         mPages.emplace_back(page);
//     }
// }

// // Limpeza dos dados, retorno ao estado inicial
// void FifoPaging::clear() {
//     mPageFault = 0;
//     mPages.clear();
// }

#include "FIFO.h"
#include "memory.h"
#include <algorithm>
#include <vector>

// Construtor com parâmetro
FifoPaging::FifoPaging(int pageCount, Memory memory) : AbstractPaging(pageCount, memory) {}

// Submissão de uma página para análise
void FifoPaging::refer(int num) {
    // memory.printPages();
    if (!memory.find(num)) {
        ++mPageFault;
        if (memory.isFull()) {
            // mPages.erase(mPages.begin()); // Remove o elemento mais antigo (FIFO)
            memory.erasePageBegin();
        }
        // mPages.push_back(num);
        memory.addPageEnd(num);
    }
}

// Limpeza dos dados, retorno ao estado inicial
void FifoPaging::clear() {
    mPageFault = 0;
    // mPages.clear();
}