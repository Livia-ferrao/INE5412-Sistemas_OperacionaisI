#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include "process.h"
#include "scheduler.h"

class FCFS: public Scheduler {

public:

    FCFS(CPU* _cpu) : Scheduler(_cpu) {}

    ~FCFS(){
        while (!ready_processes.empty()) {
            Process* process = ready_processes.front();  // Obtenha o próximo elemento da fila
            ready_processes.pop();  // Remova o elemento da fila
            delete process;  // Libere a memória do objeto Process
        }
    }

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
        //  Verifica se tem processo em execução e o tempo de execução terminou
        if (running_process != nullptr && running_process->remaining_time == 0) {
            // Salva o contexto da CPU para o processo
            running_process->state = "Finished";
            running_process->end = time;
            cpu->save_context(running_process->p_context);
            running_process = nullptr;

        }

        // Verifica se o processador está livre e tem processo na fila
        if (running_process == nullptr && !ready_processes.empty()) {
            Process* next_task = ready_processes.front();
            ready_processes.pop();
            next_task->state = "Running";
            next_task->begin = time;
            running_process = next_task;
            // Crrega o contexto do processo para a CPU
            cpu->load_context(running_process->p_context);
        }

        // Processo executando
        if (running_process != nullptr && running_process->remaining_time > 0){
            running_process->remaining_time -= 1;
        }
    }


private:
    std::queue<Process*> ready_processes;   // A List of Processes
};

#endif