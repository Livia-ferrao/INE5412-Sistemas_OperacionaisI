#ifndef SJF_H
#define SJF_H

#include <queue>
#include <vector>
#include "process.h"
#include "scheduler.h"

class SJF: public Scheduler {

public:

    // SJF(CPU* _cpu) : Scheduler(_cpu) {}

    SJF() {}

    // Verifica se alguma tarefa inicia agora
    void init_ready_queue(std::vector<Process*> processes, int time){
        for (Process *process : processes) {
            if (process->get_creation_time() == time) {
                process->set_state("Ready");
                ready_processes.push(process);
            }
        }
    }

    void processing(int time, CPU* cpu) {
        //  Verifica se tem processo em execução e o tempo de execução terminou
        if (running_process != nullptr && running_process->get_remaining_time() == 0) {
            running_process->set_state("Finished");
            running_process->set_end(time);
            // Salva o contexto da CPU para o processo
            Context context = running_process->get_p_context();
            cpu->save_context(context);
            running_process = nullptr;
        }

        // Verifica se o processador está livre e tem processo na fila
        if (running_process == nullptr && !ready_processes.empty()) {
            Process* next_process = ready_processes.top();
            ready_processes.pop();
            next_process->set_state("Running");
            next_process->set_begin(time);
            running_process = next_process;
            // Carrega o contexto do processo para a CPU
            Context context = running_process->get_p_context();
            cpu->load_context(context);
        }

        // Processo executando
         if (running_process != nullptr && running_process->get_remaining_time() > 0){
            int remaining_time = running_process->get_remaining_time(); 
            remaining_time -= 1; // Subtrai 1 do tempo restante
            running_process->set_remaining_time(remaining_time);
        }
    }


private:
    struct CompareProcessesDuration {
        bool operator()(const Process* a, const Process* b) const {
            return a->get_duration() > b->get_duration();
        }
    };
    std::priority_queue<Process*, std::vector<Process*>, CompareProcessesDuration> ready_processes;

};

#endif