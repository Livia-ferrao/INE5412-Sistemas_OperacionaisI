#ifndef FCFS_H
#define FCFS_H


#include<vector>
#include "Process.cc"

class FCFS {
    public:
        static void calculate(std::vector<Process*> processes);
};

#endif