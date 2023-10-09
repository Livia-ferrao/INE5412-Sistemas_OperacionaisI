#include "OPT.h"
#include <algorithm>
#include <limits> 

// Construtor com parâmetro
OptPaging::OptPaging(int pageCount, const std::vector<int> references) : AbstractPaging(pageCount), references(references) {}

// Submissão de uma página para análise
void OptPaging::refer(int page) {
    if (std::find(mPages.begin(), mPages.end(), page) == mPages.end()) {
        ++mPageFault;
        if (mPages.size() == mPageCount) {
            // Encontra a página mais distante no futuro e a substitui
            int indexToRemove = findPageToReplace();
            // cout << "index: " << indexToRemove << endl;
            // cout << endl;
            mPages[indexToRemove] = page;
        } else {
            mPages.push_back(page);
            references.erase(references.begin());
        }
    } else {
        references.erase(references.begin());
    }
}

// Limpeza dos dados, retorno ao estado inicial
void OptPaging::clear() {
    mPageFault = 0;
    mPages.clear();
}

int OptPaging::findPageToReplace() {
        int farthestIndex;
        int farthestDistance;
    
        // cout << "references" << endl;
        // for (int i = 0; i < references.size(); ++i) {
        //     cout <<" - " <<  references[i];
        // }
        // cout << endl;

        // cout << "mPAGES" << endl;
        // for (int i = 0; i < mPages.size(); ++i) {
        //     cout <<" - " <<  mPages[i];
        // }
        // cout << endl;

        for (int i = 0; i < mPages.size(); ++i) {
            int page = mPages[i];
            
            auto it = std::find(references.begin(), references.end(), page);
            // cout << "it - " << *it << endl;

            if (it != references.end()) {
                // cout << "VALOR ENCONTRADO" << endl;
                int futureDistance = std::distance(it, references.end());
                // cout << "Distancia: " << futureDistance << endl;
                if (i == 0){
                    farthestIndex = i;
                    farthestDistance = futureDistance;
                } else {
                     if (futureDistance < farthestDistance) {
                        farthestIndex = i;
                        farthestDistance = futureDistance;
                    }
                }
            } else {
                // cout << "VALOR NAO ENCONTRADO" << endl;
                references.erase(references.begin());
                return i;  // Se a página não for referenciada no futuro, substitui imediatamente
            }

        }
        
        references.erase(references.begin());
        return farthestIndex;
}