#ifndef PPP_H
#define PPP_H

#include <queue>
#include <vector>
#include "process.h"
#include "scheduler.h"

class PPP: public Scheduler {

public:

    PPP(CPU& _cpu) : Scheduler(_cpu) {}

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

        if ((running_process == nullptr || running_process->priority < ready_processes.top()->priority) && !ready_processes.empty()) {
            if (running_process != nullptr) {
                // Preempção: atualize o estado do processo em execução e coloque-o de volta na fila de prontidão
                running_process->state = "Ready";
                ready_processes.push(running_process);
            }
            // Selecione o próximo processo com maior prioridade
            Process* next_process = ready_processes.top();
            ready_processes.pop();
            next_process->state = "Running";
            next_process->begin = time;
            running_process = next_process;
        }

        // Processo executando
        if (running_process != nullptr && running_process->remaining_time > 0){
            running_process->remaining_time -= 1;
        }
    }


private:
    struct CompareProcessesPriority {
        bool operator()(const Process* a, const Process* b) const {
            return a->priority < b->priority; // Comparação por prioridade
        }
    };
    std::priority_queue<Process*, std::vector<Process*>, CompareProcessesPriority> ready_processes;
};

#endif