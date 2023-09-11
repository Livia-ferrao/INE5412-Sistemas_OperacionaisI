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
    // Scheduler(CPU* _cpu) : cpu(_cpu), running_process(nullptr) {}

    Scheduler():running_process(nullptr){} // Construtor padrão

    ~Scheduler() {}

    void run() {};

    virtual void init_ready_queue(std::vector<Process*> processes_queue, int time){}

    virtual void processing(int time, CPU *cpu) {}

    virtual void print_context(CPU* cpu){
        cpu->print_CPU_context();
        running_process->print_process_context();
    }
    
    virtual void print_state(std::vector<Process*> processes_queue, int time) {
        cout << time << "-" << time+1 << "\t";
            for (int i = 0; i < processes_queue.size(); i++) {
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
    // POSSO POR OS PROCESSOS AQUI PASSANDO POR CONSTRUTOR
    // std::queue<Process*> processes;   // A List of Processes
    Process* running_process;
    // CPU* cpu;
};

#endif