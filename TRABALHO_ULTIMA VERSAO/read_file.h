#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include "process.h"

class File {
public:
    File();
    ~File();

    void read_file();
    void print_processes_params();
    std::vector<Process *>& getProcesses();

private:
    std::ifstream myfile;
    std::vector<Process *> processes;
};

#endif
