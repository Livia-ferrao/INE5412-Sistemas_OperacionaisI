#ifndef OPERATING_SYSTEM_H
#define OPERATING_SYSTEM_H

#include <vector>
#include <iostream>

#include "read_file.h"
#include "process.h"
#include "scheduler.h"
#include "cpu.h"
#include "FCFS.h"
#include "SJF.h"
#include "PNP.h"
#include "PPP.h"
#include "RR.h"

class Operating_system {
public:
    Operating_system();
    ~Operating_system();

    Scheduler* init_scheduler(int scheduler_type);
    void init_processes(std::vector<Process*> processes);
    void execute(int scheduler_type);
    void run_scheduler();
    bool verify_finished_scheduling();
    void print_metrics();
    void print_processes_queue();
    void reset_process(vector<Process*> processes);

private:
    std::vector<Process*> processes_queue;
    Scheduler* scheduler;
    CPU* INE5412;
};

#endif
