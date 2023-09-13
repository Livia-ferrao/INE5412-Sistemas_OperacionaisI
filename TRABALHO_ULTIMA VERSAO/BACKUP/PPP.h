#ifndef PPP_H
#define PPP_H

#include <queue>
#include <vector>
#include "process.h"
#include "scheduler.h"

class PPP: public Scheduler {

public:

    PPP();

    ~PPP();

    void init_ready_queue(std::vector<Process*> processes, int time);

    void schedule(int time, CPU* cpu);

private:
    struct CompareProcessesPriority {
        bool operator()(const Process* a, const Process* b) const {
            return a->get_priority() < b->get_priority(); // Comparação por prioridade
        }
    };
    std::priority_queue<Process*, std::vector<Process*>, CompareProcessesPriority> ready_processes;
};

#endif