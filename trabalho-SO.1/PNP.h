#ifndef PNP_H
#define PNP_H

#include <queue>
#include <vector>
#include "process.h"
#include "scheduler.h"

class PNP: public Scheduler {

public:

    PNP(CPU* _cpu) : Scheduler(_cpu) {}

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
            // Salva o contexto da CPU para o processo
            cpu->save_context(running_process->p_context);
            running_process = nullptr;
        }

        // Verifica se o processador está livre e tem processo na fila
        if (running_process == nullptr && !ready_processes.empty()) {
            Process* next_process = ready_processes.top();
            ready_processes.pop();
            next_process->state = "Running";
            next_process->begin = time;
            running_process = next_process;
            // Crrega o contexto do processo para a CPU
            cpu->load_context(running_process->p_context);
        }

        // Processo executando
        if (running_process != nullptr && running_process->remaining_time > 0){
            running_process->remaining_time -= 1;
        }
    }


private:
    // std::queue<Process*> ready_processes;   // A List of Processes
    Process* running_process;
    struct CompareProcessesPriority {
        bool operator()(const Process* a, const Process* b) const {
            return a->priority < b->priority; // Comparação por prioridade
        }
    };

    std::priority_queue<Process*, std::vector<Process*>, CompareProcessesPriority> ready_processes;

};

#endif