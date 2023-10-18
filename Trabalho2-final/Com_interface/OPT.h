#ifndef OPT_PAGING_H
#define OPT_PAGING_H

#include "abstract_paging.h"

class OptPaging : public AbstractPaging {
public:
    // Construtor com parâmetro
    OptPaging(Memory memory, const std::vector<int> references);
    // Submissão de uma página para análise
    void refer(int page) override;
    // Limpeza dos dados, retorno ao estado inicial
    void clear(int frames, std::vector<int> newReferences) override {
        AbstractPaging::clear(frames);
        references = newReferences;
    }
    // Encontra página para ser substítuida
    int findPageToReplace();
    // Seta referências
    void setReferences(const std::vector<int>& newReferences) {
        references = newReferences;
    }

private:
    // Vetor de referências
    std::vector<int> references;
};

#endif // OPT_PAGING_H
