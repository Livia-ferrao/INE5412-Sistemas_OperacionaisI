#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <list>
#include "process.h"


class Scheduler {
public:
    Scheduler() {}
    //    FCFS(CPU& _cpu) : Scheduler(_cpu) {}


    ~Scheduler() {}

    void run() {};

    virtual void init_ready_queue(std::vector<Process*> processes, int time){
        std::cout << "Generic1: " << std::endl;  // TODO
    }

    virtual void processing() {
        std::cout << "Generic2: " << std::endl;  // TODO
    }

    virtual void finish_processing() {
        std::cout << "Generic3: " << std::endl;  // TODO
    }
    
    virtual void print_metrics() {
        std::cout << "Generic4: " << std::endl;  // TODO
    }

public:
    std::list<Process*> processes;   // A List of Processes
    Process* current_process;
    int processes_size;
};

#endif