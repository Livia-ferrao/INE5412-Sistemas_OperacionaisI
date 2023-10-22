#ifndef OPT_PAGING_H
#define OPT_PAGING_H

#include "abstract_paging.h"

class OptPaging : public AbstractPaging {
    public:
        // Construtor com parâmetro
        OptPaging(Memory memory, const std::vector<int> references);
        // Seta tabela de referências
        void setRefTable(vector<int> references) override;
        // Submissão de uma página para análise
        void refer(int page) override;
        // Encontra página a ser substituída
        int findPageToReplace();

    private:
        // Tabela de referências
        std::vector<vector<int>> referencesTable;
};

#endif // OPT_PAGING_H