#include "OPT.h"
#include <algorithm>
#include <limits>

// Construtor com parâmetro
OptPaging::OptPaging(Memory memory, const std::vector<int> references) : AbstractPaging(memory), references(references) {}

// Submissão de uma página para análise
void OptPaging::refer(int num) {
    // Verifica se referência foi encontrada no vetor de páginas
    if (!memory.find(num)) {
        // Mais uma falta de página
        ++pageFault;
        // Verifica se a memória está cheia 
        if (memory.isFull()) {
            // Encontra a página mais distante no futuro
            int indexToRemove = findPageToReplace();
            // Substitui a página pelo índice
            memory.replacePage(indexToRemove, num);
        } else {
            // Adiciona página no final
            memory.addPageEnd(num);
            // Deleta primeira referência
            references.erase(references.begin());
        }
    } else {
        // Deleta primeira referência
        references.erase(references.begin());
    }
}

int OptPaging::findPageToReplace() {
        // ìndice da página mais longe
        int farthestIndex = -1;
        // Distância da página mais longe
        int farthestDistance = -1; 

        // Loop para cada página da memória
        for (int i = 0; i < memory.getPages().size(); ++i) {
            // Pega valor da página
            int page = memory.getPages()[i].getValue();
            // Procura a próxima referência a essa página
            auto nextReference = std::find(references.begin(), references.end(), page);
            // Se a referência não existir nas próximas referências retorna o índice
            if (nextReference == references.end()) {
                references.erase(references.begin());
                return i;
            }
            // Calcula distância da próxima referência
            int distance = std::distance(references.begin(), nextReference);
            // Verifica qual página tem a mais distância para ser substítuida
            if (distance > farthestDistance) {
                farthestDistance = distance;
                farthestIndex = i;
            }
        }
        // Deleta primeira referência
        references.erase(references.begin());
        return farthestIndex;
}