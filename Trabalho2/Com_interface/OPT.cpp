#include "OPT.h"
#include <algorithm>
#include <limits> 

// Construtor com parâmetro
OptPaging::OptPaging(Memory memory, const std::vector<int> references) : AbstractPaging(memory) {}

// Criação da matriz de referências
void OptPaging::setRefTable(vector<int> references){

    // Seta tamanho para a tabela
    int max_value = *max_element(references.begin(), references.end());
    referencesTable.resize(max_value + 1);

    // Seta valor para a tabela
    for (int i = 0; i < references.size(); i++){
        referencesTable[references[i]].push_back(i);
    }
}

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
            // Deleta página da tabela de referências
            referencesTable[num].erase(referencesTable[num].begin());
        } else {
            // Adiciona página no final
            memory.addPageEnd(num);
            // Deleta página da tabela de referências
            referencesTable[num].erase(referencesTable[num].begin());
        }
    } else {
        // Deleta página da tabela de referências
        referencesTable[num].erase(referencesTable[num].begin());
    }
}

int OptPaging::findPageToReplace() {
    // Distância da página mais longe
    int farthestDistance = -1; 
    // Índice da página mais longe
    int farthestIndex = -1;
    // Loop para cada página da memória
    for (int i = 0; i < memory.getPages().size(); i++) {
        // Pega valor da página
        int page = memory.getPages()[i].getValue();
        // Verifica se o valor é vazio
        if (referencesTable[page].empty()){
            // Retorna índice
            return i;
        } 
        // Verifica menor distância
        if (farthestDistance < referencesTable[page][0]){
            // Atribui a maior distância
            farthestDistance = referencesTable[page][0];
            // Índice da maior distância
            farthestIndex = i;
        }
    }
    // Retorna índice
    return farthestIndex;
}
