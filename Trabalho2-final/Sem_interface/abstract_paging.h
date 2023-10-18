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
    // Obter a quantidade de falta de páginas
    virtual int getPageFaultCount() { return pageFault; }
    // Limpar os dados, retornar ao estado inicial
    virtual void reset() { pageFault = 0; }
    // Destrutor
    virtual ~AbstractPaging() {}

  protected:
    // Número atual de falhas de página
    int pageFault = 0;
    // Memória
    Memory memory;
};

#endif // ABSTRACT_PAGING_H