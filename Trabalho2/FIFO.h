#ifndef FIFO_PAGING_H
#define FIFO_PAGING_H
#include "abstract_paging.h"

class FifoPaging : public AbstractPaging {
  public:
    // Construtor com parâmetro
    FifoPaging(int pageCount, Memory memory);
    // Submissão de uma página para análise
    void refer(int page) override;
    // Limpeza dos dados, retorno ao estado inicial
    void clear() override;
};

#endif // FIFO_PAGING_H