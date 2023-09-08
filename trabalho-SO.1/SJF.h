#ifndef SJF_H
#define SJF_H

#include <queue>
#include <vector>
#include "process.h"
#include "scheduler.h"

class SJF: public Scheduler {

public:

    SJF() {};

    // Verifica se alguma tarefa inicia agora
    void init_ready_queue(std::vector<Process*> processes, int time){
        for (Process *process : processes) {
            if (process->creation_time == time) {
                process->state = "Ready";
                ready_processes.push(process);
            }
        }
    }

    void processing(int time) {
        //  Verifica se tem processo em execução e ainda tem tempo de execução
        if (running_process != nullptr && running_process->remaining_time == 0) {
            running_process->state = "Finished";
            running_process->end = time;
            running_process = nullptr;
        }

        // Verifica se o processador está livre e tem processo na fila
        if (running_process == nullptr && !ready_processes.empty()) {
            Process* next_task = ready_processes.top();
            ready_processes.pop();
            next_task->state = "Running";
            next_task->begin = time;
            running_process = next_task;
        }

        // Processo executando
        if (running_process != nullptr && running_process->remaining_time > 0){
            running_process->remaining_time -= 1;
        }
    }


private:
    // std::queue<Process*> ready_processes;   // A List of Processes
    Process* running_process;
    int processes_size;

    struct CompareProcessesDuration {
        bool operator()(const Process* a, const Process* b) const {
            return a->duration > b->duration;
        }
    };
    std::priority_queue<Process*, std::vector<Process*>, CompareProcessesDuration> ready_processes;

};

#endif