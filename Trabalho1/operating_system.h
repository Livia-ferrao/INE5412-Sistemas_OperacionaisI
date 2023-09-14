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

    void execute(int scheduler_type);

private:
    std::vector<Process*> processes_queue;
    Scheduler* scheduler;
    CPU* INE5412;

    Scheduler* init_scheduler(int scheduler_type);
    void init_processes(std::vector<Process*> processes);
    void run_scheduler();
    bool verify_finished_scheduling();
    void print_metrics();
    void print_processes_queue();
};

#endif
