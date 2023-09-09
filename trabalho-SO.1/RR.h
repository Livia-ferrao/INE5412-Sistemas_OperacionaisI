#ifndef RR_H
#define RR_H

#include <queue>
#include <vector>
#include "process.h"
#include "scheduler.h"

class RR: public Scheduler {

public:

    RR(CPU& _cpu) : Scheduler(_cpu) {}

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
        //  Verifica se tem processo em execução e não tem mais tempo de execução ou tempo de quantum
        if (running_process != nullptr && (running_process->remaining_time == 0 || time_slice_remaining_ == 0)) {
            if (running_process->remaining_time == 0) {
                running_process->state = "Finished";
                running_process->end = time;
            } else {
                running_process->state = "Ready";
                ready_processes.push(running_process);
            }
            running_process = nullptr;
            time_slice_remaining_ = RR_QUANTUM;
        }

        // Verifica se o processador está livre e tem processo na fila
        if (running_process == nullptr && !ready_processes.empty()) {
            Process* next_process = ready_processes.front();
            ready_processes.pop();
            next_process->state = "Running";
            next_process->begin = time;
            running_process = next_process;
            time_slice_remaining_ = RR_QUANTUM;
        }

        // Processo executando
        if (running_process != nullptr && running_process->remaining_time > 0){
            running_process->remaining_time -= 1;
            time_slice_remaining_ -= 1;
        }
    }


private:
    std::queue<Process*> ready_processes;   
    const int RR_QUANTUM = 2;
    int time_slice_remaining_;
};

#endif