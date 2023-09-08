#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include "process.h"
#include "scheduler.h"

class FCFS: public Scheduler {

public:

    FCFS() {};

    void init_ready_queue(std::vector<Process*> processes, int time){
        std::cout << "Generic1: " << std::endl;  // TODO
    }

    void processing() {
        std::cout << "Generic2: " << std::endl;  // TODO
    }

    void finish_processing() {
        std::cout << "Generic3: " << std::endl;  // TODO
    }
    
    void print_metrics() {
        std::cout << "Generic4: " << std::endl;  // TODO
    }

private:
    std::queue<Process*> processes;   // A List of Processes
    Process* current_process;
    int processes_size;
};

#endif