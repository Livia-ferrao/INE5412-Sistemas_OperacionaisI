#ifndef OPERATING_SYSTEM_H
#define OPERATING_SYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#include "process.h"
#include "scheduler.h"
#include "cpu.cpp"
// #include "constantes.h"
using namespace std;


class Operating_system {

    public:
        Operating_system();

        ~Operating_system();

        void execute(int scheduler_type);                 

    private:
        Scheduler* init_scheduler(int scheduler_type);
        void init_processes(vector<Process*> processes);
        void print_processes_queue();
        bool verify_all_finished(int allFinished);
        void run_scheduler(); 
        
        vector<Process *> processes_queue;
        Scheduler* scheduler;
        CPU* cpu;
        int time;
};

#endif