#ifndef RR_H
#define RR_H

#include <queue>
#include <vector>
#include "process.h"
#include "scheduler.h"

class RR: public Scheduler {

public:

    RR();

    ~RR();

    void init_ready_queue(std::vector<Process*> processes, int time);

    void schedule(int time, CPU* cpu);


private:
    std::queue<Process*> ready_processes;   
    const int RR_QUANTUM = 2;
    int time_slice_remaining_;
};

#endif