#ifndef RR_H
#define RR_H

#include <queue>
#include <vector>
#include "process.h"
#include "scheduler.h"
#include "cpu.h"

class RR : public Scheduler {
public:
    RR() : time_slice_remaining_(RR_QUANTUM) {}

    ~RR() {}

    void init_ready_queue(std::vector<Process*> processes, int time) override;

    void schedule(int time, CPU* cpu) override;

private:
    std::queue<Process*> ready_processes;
    const int RR_QUANTUM = 2;
    int time_slice_remaining_;
};

#endif
