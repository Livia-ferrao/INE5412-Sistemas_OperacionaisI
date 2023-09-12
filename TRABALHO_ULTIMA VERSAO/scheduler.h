#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <ostream>

#include "process.h"
#include "cpu.h"

class Scheduler {
public:
    Scheduler(): running_process(nullptr){} // Construtor padrão

    virtual ~Scheduler() {};

    virtual void init_ready_queue(std::vector<Process*> processes_queue, int time) = 0;

    virtual void schedule(int time) = 0;

    virtual void print_context(){
        CPU::print_CPU_context();
        running_process->print_process_context();
    }
    
    virtual void print_state(std::vector<Process*> processes_queue, int time) {
        cout << time << "-" << time+1 << "\t";
            int size = processes_queue.size();
            for (int i = 0; i < size; i++) {
                if (processes_queue[i]->get_state() == "Running"){
                    cout << "XX |"; 
                } else if(processes_queue[i]->get_state() == "Ready"){
                    cout << "-- |";
                } else if(processes_queue[i]->get_state() == "Finished"){
                    cout << "   |";
                } else {
                    cout << "   |";
                }
            }
        cout << endl;
    }

protected:
    Process* running_process = nullptr;
};

#endif