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

class Scheduler {
public:
    Scheduler() {}
    //    FCFS(CPU& _cpu) : Scheduler(_cpu) {}


    ~Scheduler() {}

    void run() {};

    virtual void init_ready_queue(std::vector<Process*> processes, int time){}

    virtual void processing(int time) {}
    
    virtual void print_state(std::vector<Process*> processes_queue, int time) {
        cout << time << "-" << time+1 << "\t";
            for (int i = 0; i < processes_queue.size(); i++) {
                if (processes_queue[i]->state == "Running"){
                    cout << "XX |"; 
                } else if(processes_queue[i]->state == "Ready"){
                    cout << "-- |";
                } else if(processes_queue[i]->state == "Finished"){
                    cout << "   |";
                } else {
                    cout << "   |";
                }
            }
        cout << endl;
    }

    virtual void print_metrics() {}
public:
    // POSSO POR OS PROCESSOS AQUI PASSANDO POR CONSTRUTOR
    std::queue<Process*> processes;   // A List of Processes
};

#endif