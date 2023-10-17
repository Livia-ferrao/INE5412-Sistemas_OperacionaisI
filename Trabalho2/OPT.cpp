// #include "OPT.h"
// #include <algorithm>
// #include <limits> 
// #include <unordered_map>
// #include <chrono>


// // Construtor com parâmetro
// OptPaging::OptPaging(Memory memory, const std::vector<int> references) : AbstractPaging(memory), references(references) {}



// // Submissão de uma página para análise
// void OptPaging::refer(int page) {
//     //std::find(mPages.begin(), mPages.end(), page) == mPages.end()
//     if (!memory.find(page)) {
//         ++mPageFault;
//         //mPages.size() == mPageCount
//         if (memory.isFull()) {
//             // Encontra a página mais distante no futuro e a substitui
//             int indexToRemove = findPageToReplace();
//             // memory.erasePage(index);
//             memory.replacePage(indexToRemove, page);
//             // memory.pages[indexToRemove] = page;
//         } else {
//             memory.addPageEnd(page);
//             // mPages.push_back(page);
//             references.erase(references.begin());
//         }
//     } else {
//         references.erase(references.begin());
//     }
// }

// // Limpeza dos dados, retorno ao estado inicial
// void OptPaging::clear() {
//     mPageFault = 0;
// }


// int OptPaging::findPageToReplace() {
//         int farthestIndex = -1;
//         int farthestDistance = -1; 
//         // cout << "----- SAIU ---- "<< endl;
//         // memory.printPages();
//         // print references
//         // cout << "REFERENCES: ";
//         // for(int z = 0; z < references.size(); z++){
//         //     cout << references[z] << "-";
//         // }
//         // cout << endl;

//         for (int i = 0; i < memory.getPages().size(); ++i) {
//             int page = memory.getPages()[i].getValue();
//             // Procura a próxima referência a essa página
//             auto nextReference = std::find(references.begin(), references.end(), page);

//             if (nextReference == references.end()) {
//                 references.erase(references.begin());
//                 return i;
//             }

//             int distance = std::distance(references.begin(), nextReference);
//             if (distance > farthestDistance) {
//                 farthestDistance = distance;
//                 farthestIndex = i;
//             }
//         }
        
//         references.erase(references.begin());
//         return farthestIndex;
// }

#include "OPT.h"
#include <algorithm>
#include <limits> 
#include <unordered_map>
#include <chrono>

OptPaging::OptPaging(Memory memory, const std::vector<int> references) : AbstractPaging(memory), references(references) {}

void OptPaging::refer(int page) {
    if (!memory.find(page)) {
        ++mPageFault;
        if (memory.isFull()) {
            int indexToRemove = findPageToReplace();
            memory.replacePage(indexToRemove, page);
        } else {
            memory.addPageEnd(page);
        }
    }
    references.erase(references.begin());
}

void OptPaging::clear() {
    mPageFault = 0;
}

int OptPaging::findPageToReplace() {
    int farthestIndex = -1;
    int farthestDistance = -1;
    std::unordered_map<int, int> nextPageIndices;

    for (int i = 0; i < references.size(); ++i) {
        int page = references[i];
        if (nextPageIndices.find(page) == nextPageIndices.end()) {
            nextPageIndices[page] = i;
        }
    }

    for (int i = 0; i < memory.getPages().size(); ++i) {
        int page = memory.getPages()[i].getValue();
        int nextReference = nextPageIndices[page];
        if (nextReference == references.size()) {
            references.erase(references.begin());
            return i;
        }
        int distance = nextReference - i;
        if (distance > farthestDistance) {
            farthestDistance = distance;
            farthestIndex = i;
        }
    }

    references.erase(references.begin());
    return farthestIndex;
}

// #include "OPT.h"
// #include <unordered_map>
// #include <deque>
// #include <algorithm>
// #include <iostream>
// #include <list>

// OptPaging::OptPaging(Memory memory, const std::vector<int> references) : AbstractPaging(memory), references(references) {}

// void OptPaging::refer(int page) {
//     if (!memory.find(page)) {
//         ++mPageFault;
//         if (memory.isFull()) {
//             int indexToRemove = findPageToReplace();
//             memory.replacePage(indexToRemove, page);
//         } else {
//             memory.addPageEnd(page);
//         }
//     }
//     references.pop_front();
// }

// void OptPaging::clear() {
//     mPageFault = 0;
// }

// int OptPaging::findPageToReplace() {
//     int farthestIndex = -1;
//     int farthestDistance = -1;
//     std::unordered_map<int, int> nextPageIndices;
//     std::deque<int> referencesCopy(references.begin(), references.end());

//     for (int i = referencesCopy.size() - 1; i >= 0; --i) {
//         int page = referencesCopy[i];
//         if (nextPageIndices.find(page) == nextPageIndices.end()) {
//             nextPageIndices[page] = i;
//         }
//     }

//     for (int i = 0; i < memory.getPages().size(); ++i) {
//         int page = memory.getPages()[i].getValue();
//         int nextReference = nextPageIndices[page];
//         if (nextReference == references.size()) {
//             references.pop_front();
//             return i;
//         }
//         int distance = nextReference - i;
//         if (distance > farthestDistance) {
//             farthestDistance = distance;
//             farthestIndex = i;
//         }
//     }

//     references.pop_front();
//     return farthestIndex;
// }

