#ifndef PNP_H
#define PNP_H

#include <queue>
#include <vector>
#include "process.h"
#include "scheduler.h"
#include "cpu.h"

class PNP : public Scheduler {
public:
    PNP() {}

    ~PNP() {}

    void init_ready_queue(std::vector<Process*> processes, int time) override;

    void schedule(int time, CPU* cpu) override;

private:
    struct CompareProcessesPriority {
        bool operator()(const Process* a, const Process* b) const {
            return a->get_priority() > b->get_priority(); // Comparação por prioridade (maior prioridade tem maior valor)
        }
    };
    std::priority_queue<Process*, std::vector<Process*>, CompareProcessesPriority> ready_processes;
};

#endif
