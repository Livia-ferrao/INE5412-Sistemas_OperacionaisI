#ifndef SJF_H
#define SJF_H

#include <queue>
#include <vector>
#include "process.h"
#include "scheduler.h"
#include "cpu.h" // Certifique-se de incluir o arquivo de cabeçalho da classe CPU

class SJF : public Scheduler {
public:
    SJF() {}

    ~SJF() {}

    void init_ready_queue(std::vector<Process*> processes, int time) override;

    void schedule(int time) override;

private:
    struct CompareProcessesDuration {
        bool operator()(const Process* a, const Process* b) const {
            return a->get_duration() > b->get_duration();
        }
    };
    std::priority_queue<Process*, std::vector<Process*>, CompareProcessesDuration> ready_processes;
};

#endif
