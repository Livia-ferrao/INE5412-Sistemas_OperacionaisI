#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include <queue>
#include "process.h"
#include "scheduler.h"
#include "cpu.h" // Certifique-se de incluir o arquivo de cabeçalho da classe CPU

class FCFS : public Scheduler {
public:
    FCFS() {}

    ~FCFS() {}

    void init_ready_queue(std::vector<Process*> processes, int time) override;

    void schedule(int time, CPU* cpu) override;

private:
    std::queue<Process*> ready_processes;
};

#endif
