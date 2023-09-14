#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <iostream>
#include "process.h"
#include "cpu.h"

class Scheduler {
public:
    Scheduler() : running_process(nullptr) {} // Construtor padrão

    virtual ~Scheduler() {};

    virtual void init_ready_queue(std::vector<Process*> processes_queue, int time) = 0;

    virtual void schedule(int time, CPU* INE5412) = 0;

    virtual void print_context(CPU* INE5412);

    virtual void print_state(std::vector<Process*> processes_queue, int time);

protected:
    Process* running_process;
};

#endif
