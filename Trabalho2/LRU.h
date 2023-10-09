#ifndef LRU_PAGING_H
#define LRU_PAGING_H

#include "abstract_paging.h"

class LruPaging : public AbstractPaging {
  public:
    // Construtor com parâmetro
    LruPaging(int pageCount);
    // Submissão de uma página para análise
    void refer(int page) override;
    // Limpeza dos dados, retorno ao estado inicial
    void clear() override;
};

#endif // LRU_PAGING_H