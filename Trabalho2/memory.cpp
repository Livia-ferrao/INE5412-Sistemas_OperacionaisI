#include "memory.h"
#include "page.h"
#include <iostream>

Memory::Memory(int numFrames) : num_frames(numFrames) {}

void Memory::addPageEnd(int num){
    Page page(num);
    pages.push_back(page);
}

void Memory::erasePageBegin(){
    pages.erase(pages.begin()); 
}

void Memory::erasePage(int num){
    pages.erase(std::remove_if(pages.begin(), pages.end(),
                       [num](const Page& page) { return page.getValue() == num; }),
                    pages.end());
}

void Memory::replacePage(int index, int num) {
    if (index >= 0 && index < pages.size()) {
        pages[index] = Page(num);
    } else {
        std::cout << "Índice fora dos limites." << std::endl;
    }
}

bool Memory::isFull(){
    return pages.size() == num_frames;
}

bool Memory::isEmpty(){
    return pages.empty();
}

bool Memory::find(int num){
    // std::find(pages.begin(), pages.end(), num) == pages.end();
    auto it = std::find_if(pages.begin(), pages.end(),
                           [num](const Page& page) { return page.getValue() == num; });

    return it != pages.end();
}

void Memory::printPages() {
    std::cout << "Vetor de páginas: ";
    for (const auto& page : pages) {
        std::cout << page.getValue() << " ";
    }
    std::cout << std::endl;
}

void Memory::clearPages() {
    pages.clear();
}

std::vector<Page> Memory::getPages() {
    return pages;
}

void Memory::setPages(std::vector<Page>& newPages) {
    pages = newPages;
}

int Memory::getNumFrames() {
   return num_frames;
}

void Memory::setNumFrames(int newNumFrames) {
    num_frames = newNumFrames;
}