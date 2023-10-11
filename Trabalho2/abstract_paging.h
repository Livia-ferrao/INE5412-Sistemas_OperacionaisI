#ifndef ABSTRACT_PAGING_H
#define ABSTRACT_PAGING_H

#include <list>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "memory.h"

using namespace std;

// Classe abstrata de substituição de página
class AbstractPaging {
  public:
    // Construtor com parâmetro
    AbstractPaging(int pageCount, Memory memory) : mPageCount(pageCount), memory(memory) {
        if (pageCount <= 0)
            throw std::invalid_argument("FrameCount <= 0");
    }
    // Submeter a página para avaliação
    virtual void refer(int page) = 0;
    // Obter a lista de páginas
    // virtual const std::vector<int> getList() { return mPages; };
    // Obter a quantidade de falta de páginas
    virtual int getPageFaultCount() { return mPageFault; }
    // Limpar os dados, retornar ao estado inicial
    virtual void clear() = 0;
    // Destrutor virtual (obrigatório)
    virtual ~AbstractPaging() {}

  protected:
    // Número máximo de páginas na memória
    int mPageCount;
    // Número atual de falhas de página
    int mPageFault = 0;
    // Fila de páginas
    // std::vector<int> mPages;
    Memory memory;
};

#endif // ABSTRACT_PAGING_H