#ifndef OPT_PAGING_H
#define OPT_PAGING_H

#include "abstract_paging.h"

class OptPaging : public AbstractPaging {
    public:
        // Construtor com parâmetro
        OptPaging(Memory memory, const std::vector<int> references);
        // Submissão de uma página para análise
        void refer(int page) override;
        // Encontra página a ser substituída
        int findPageToReplace();

    private:
        // Vetor de referências
        std::vector<int> references;
};

#endif // OPT_PAGING_H