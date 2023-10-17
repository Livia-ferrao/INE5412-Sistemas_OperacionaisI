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
    AbstractPaging(Memory memory) : memory(memory) {}
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
    // Número atual de falhas de página
    int mPageFault = 0;
    // Memória
    Memory memory;
};

#endif // ABSTRACT_PAGING_H