#ifndef ABSTRACT_PAGING_H
#define ABSTRACT_PAGING_H

#include <list>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <QString>
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
    // Obter memória
    virtual Memory getMemory() {return memory; }
    // Limpar os dados, retornar ao estado inicial
    virtual void clear(int frames, std::vector<int> = {}) {
        pageFault = 0;
        memory.clearPages();
        memory.setNumFrames(frames);
    }
    // Destrutor virtual (obrigatório)
    virtual ~AbstractPaging() {}
    // Atualiza interface gráfica
    virtual QString update_gui(int page){
        // Captura o número atual de faltas de página
        int pageFaultCountBefore = getPageFaultCount();
        // Submete a página para avaliação
        refer(page);
        // Captura o número de faltas de página após a submissão
        int pageFaultCountAfter = getPageFaultCount();
        // Constrói uma string representando o estado atual
        QString resultLine = QString::number(page) + ": ";
        std::vector<Page> list = memory.getPages();
        for (auto page : list) {
            resultLine += QString::number(page.getValue()) + ", ";
        }
        resultLine.chop(2);
        if (pageFaultCountBefore != pageFaultCountAfter) {
            resultLine += " [Falta de pagina]";
        }
        return resultLine;
    }

protected:
    // Número atual de falhas de página
    int pageFault = 0;
    // Memória
    Memory memory;
};

#endif // ABSTRACT_PAGING_H
