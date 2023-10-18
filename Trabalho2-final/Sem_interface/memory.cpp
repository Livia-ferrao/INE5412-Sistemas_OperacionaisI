#include "memory.h"

// Construtor da classe Memory
Memory::Memory(int numFrames) : num_frames(numFrames) {}

// Adiciona uma página ao final do vetor de páginas
void Memory::addPageEnd(int num){
    Page page(num);
    pages.push_back(page);
}

// Remove a página do início do vetor de páginas
void Memory::erasePageBegin(){
    pages.erase(pages.begin()); 
}

// Remove a página com o número especificado do vetor de páginas
void Memory::erasePage(int num){
    pages.erase(std::remove_if(pages.begin(), pages.end(), [num](const Page& page) { return page.getValue() == num; }), pages.end());
}

// Substitui a página no índice especificado por uma nova página com o número especificado
void Memory::replacePage(int index, int num) {
    if (index >= 0 && index < pages.size()) {
        pages[index] = Page(num);
    } else {
        std::cout << "Índice fora dos limites." << std::endl;
    }
}

// Verifica se a memória está cheia
bool Memory::isFull(){
    return pages.size() == num_frames;
}

// Verifica se a memória está vazia
bool Memory::isEmpty(){
    return pages.empty();
}

// Verifica se a página com o número especificado está presente na memória
bool Memory::find(int num){
    auto it = std::find_if(pages.begin(), pages.end(), [num](const Page& page) { return page.getValue() == num; });
    return it != pages.end();
}

// Imprime as páginas presentes na memória
void Memory::printPages() {
    std::cout << "Vetor de páginas: ";
    for (const auto& page : pages) {
        std::cout << page.getValue() << " ";
    }
    std::cout << std::endl;
}

// Limpa todas as páginas da memória
void Memory::clearPages() {
    pages.clear();
}

// Retorna o vetor de páginas
std::vector<Page> Memory::getPages() {
    return pages;
}

// Retorna o número de quadros na memória
int Memory::getNumFrames() {
   return num_frames;
}

// Define um novo número de quadros na memória
void Memory::setNumFrames(int newNumFrames) {
    num_frames = newNumFrames;
}