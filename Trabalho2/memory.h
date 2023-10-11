#ifndef MEMORY_H
#define MEMORY_H

#include <algorithm>
#include <vector>
#include "page.h"

class Memory {
    public:
        Memory(int numFrames);
        bool isEmpty();
        bool isFull();
        bool find(int num);
        void addPageEnd(int num);
        void erasePageBegin();
        void erasePage(int num);
        void printPages();
        void clearPages();
        std::vector<Page> getPages();
        void setPages(std::vector<Page>& pages);
        int getNumFrames();
        void setNumFrames(int num_frames);

    public:
        std::vector<Page> pages;
        int num_frames;
};

#endif // MEMORY_H