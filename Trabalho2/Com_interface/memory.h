#ifndef MEMORY_H
#define MEMORY_H

#include <algorithm>
#include <iostream>
#include <vector>
#include "page.h"

class Memory {
    public:
        // Construtor
        Memory(int numFrames);
        // Verificação se vetor está vazio
        bool isEmpty();
        // Verificação se vetor está cheio
        bool isFull();
        // Encontra página pelo número de referencia
        bool find(int num);
        // Adiciona página no final
        void addPageEnd(int num);
        // Apaga página do início
        void erasePageBegin();
        // Apaga página pelo número da página
        void erasePage(int num);
        // Imprime valor das páginas
        void printPages();
        // Apaga vetor de páginas
        void clearPages();
        // Substitui página na memória 
        void replacePage(int index, int newPageValue);
        // Retorna vetor de páginas
        std::vector<Page> getPages();
        // Retorna número de frames
        int getNumFrames();
        // Seta número de frames
        void setNumFrames(int num_frames);

    private:
        // Vetor de páginas
        std::vector<Page> pages;
        // Número de frames
        int num_frames;
};

#endif // MEMORY_H