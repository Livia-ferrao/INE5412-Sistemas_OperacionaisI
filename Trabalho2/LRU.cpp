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
#include <algorithm>
#include <vector>

// Construtor com parâmetro
LruPaging::LruPaging(int pageCount) : AbstractPaging(pageCount) {}

// Submissão de uma página para análise
void LruPaging::refer(int page) {
    auto duplicate = std::find(mPages.begin(), mPages.end(), page);
    if (duplicate == mPages.end()) {
        ++mPageFault;
        if (mPages.size() == mPageCount) {
            mPages.erase(mPages.begin()); // Remove o elemento menos recentemente usado (LRU)
        }
        mPages.push_back(page);
    } else {
        mPages.erase(std::remove(mPages.begin(), mPages.end(), page), mPages.end());
        mPages.push_back(page);
    }
}

// Limpeza dos dados, retorno ao estado inicial
void LruPaging::clear() {
    mPageFault = 0;
    mPages.clear();
}