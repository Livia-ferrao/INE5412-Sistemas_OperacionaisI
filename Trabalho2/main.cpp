#include <iostream>
#include <memory>
#include <vector>
#include "abstract_paging.h"
#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"
#include "memory.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Leitura da entrada
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <num_frames>" << endl;
        return 1;
    }
    // Número de frames da memória RAM
    int num_frames = stoi(argv[1]);
    // Ponteiro para o algoritmo de substituição de página
    std::unique_ptr<AbstractPaging> pagingFIFO;
    std::unique_ptr<AbstractPaging> pagingLRU;
    std::unique_ptr<AbstractPaging> pagingOPT;

    // Vetor de páginas
    vector<int> references;
    // Cada linha do arquivo uma página
    int page;
    // Vetor recebe as páginas
    // while (cin >> page) {
    //     references.push_back(page);
    // }
    while (!feof(stdin))
    {
        scanf("%d",&page);
        references.push_back(page);
    }


    cout << num_frames << " quadros" << endl;
    cout << references.size() -1 << " refs" << endl;

    Memory memory(num_frames);
    // memory.addPageEnd(1);
    // memory.addPageEnd(7);
    // memory.addPageEnd(5);
    // memory.addPageEnd(4);

    // memory.printPages();

    // int a = memory.find(2);

    // cout << a << endl;
    // cout << "Vetor de paginas: " << endl;
    // for(int i; i<memory.pages.size(); i++){
    //     cout << memory.pages[i].getValue() << " - ";
    // }
    // cout << endl;


     // FIFO, LRU e OPT
    pagingFIFO = std::unique_ptr<AbstractPaging>(new FifoPaging(num_frames, memory));
    pagingLRU = std::unique_ptr<AbstractPaging>(new LruPaging(num_frames, memory));
    pagingOPT = std::unique_ptr<AbstractPaging>(new OptPaging(num_frames, memory, references));

    for(int page: references ){
        pagingFIFO->refer(page);
        pagingLRU->refer(page);
        pagingOPT->refer(page);
    }


     // Quantidade de faltas de páginas
    std::cout << "FIFO: " << pagingFIFO->getPageFaultCount() << std::endl;
    std::cout << "LRU: " << pagingLRU->getPageFaultCount() << std::endl;
    std::cout << "OPT: " << pagingOPT->getPageFaultCount() << std::endl;


    // ===== LRU ======
    //  for(int page: references ){
    //     paging->refer(page);
    // }
    //  // Quantidade de faltas de páginas
    // std::cout << "LRU: " << paging->getPageFaultCount() << std::endl;

    // // Iterando sobre a lista e imprimindo cada elemento
    // // for (int page : paging->getList()) {
    // //     std::cout << page << " ";
    // // }
    // paging->clear();

    
    // ===== OPT ======
    // paging = std::unique_ptr<AbstractPaging>(new OptPaging(num_frames, references));
    //  for(int page: references ){
    //     paging->refer(page);
    // }
    //  // Quantidade de faltas de páginas
    // std::cout << "OPT: " << paging->getPageFaultCount() << std::endl;

    // // // Iterando sobre a lista e imprimindo cada elemento
    // // for (int page : paging->getList()) {
    // //     std::cout << page << " ";
    // // }
    // paging->clear();
    




    // Fazendo downcast para FifoPaging
    // FifoPaging* fifoPaging = dynamic_cast<FifoPaging*>(paging.get());

    // // Quantidade de faltas de páginas
    // std::cout << paging->getPageFaultCount() << std::endl;

    // // Iterando sobre a lista e imprimindo cada elemento
    // for (int page : paging->getList()) {
    //     std::cout << page << " ";
    // }
 
}