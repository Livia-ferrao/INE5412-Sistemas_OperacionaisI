#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include "process.h"
#include "scheduler.h"

class FCFS: public Scheduler {

public:

    FCFS() {}
    ~FCFS(){}    
    void init_ready_queue(std::vector<Process*> processes, int time);
    void schedule(int time, CPU *cpu);

private:
    std::queue<Process*> ready_processes;
};

#endif