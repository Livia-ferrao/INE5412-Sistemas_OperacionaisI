// #include "LRU.h"
// #include <algorithm>

// // Construtor com parâmetro
// LruPaging::LruPaging(int pageCount) : AbstractPaging(pageCount) {}

// // Submissão de uma página para análise
// void LruPaging::refer(int page) {
//     auto duplicate = std::find(mPages.begin(), mPages.end(), page);
//     if (duplicate == mPages.end()) {
//         ++mPageFault;
//         if ((long)mPages.size() == (long)mPageCount) {
//             mPages.pop_front();
//         }
//         mPages.emplace_back(page);
//     } else {
//         mPages.remove(page);
//         mPages.emplace_back(page);
//     }
// }

// // Limpeza dos dados, retorno ao estado inicial
// void LruPaging::clear() {
//     mPageFault = 0;
//     mPages.clear();
// }

#include "LRU.h"
#include "memory.h"
#include <algorithm>
#include <vector>

// Construtor com parâmetro
LruPaging::LruPaging(Memory memory) : AbstractPaging(memory) {}

// Submissão de uma página para análise
void LruPaging::refer(int page) {
    // auto duplicate = std::find(mPages.begin(), mPages.end(), page);
    // duplicate == mPages.end()
    // memory.printPages();
    if (!memory.find(page)) {
        ++mPageFault;
        // mPages.size() == mPageCount
        if(memory.isFull()) {
            // mPages.erase(mPages.begin()); // Remove o elemento menos recentemente usado (LRU)
            memory.erasePageBegin();
        }
        // mPages.push_back(page);
        memory.addPageEnd(page);
    } else {
        memory.erasePage(page);
        memory.addPageEnd(page);
        // mPages.erase(std::remove(mPages.begin(), mPages.end(), page), mPages.end());
        // mPages.push_back(page);
    }
}

// Limpeza dos dados, retorno ao estado inicial
void LruPaging::clear() {
    mPageFault = 0;
    // mPages.clear();
}