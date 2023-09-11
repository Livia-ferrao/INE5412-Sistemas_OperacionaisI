#ifndef RR_H
#define RR_H

#include <queue>
#include <vector>
#include "process.h"
#include "scheduler.h"

class RR: public Scheduler {

public:

    // RR(CPU* _cpu) : Scheduler(_cpu) {}

    RR() {}

    ~RR() {}

    // Verifica se alguma tarefa inicia agora
    void init_ready_queue(std::vector<Process*> processes, int time){
         for (Process *process : processes) {
            if (process->get_creation_time() == time) {
                process->set_state("Ready");
                ready_processes.push(process);
            }
        }
    }

    void scheduler(int time, CPU* cpu) {
        //  Verifica se tem processo em execução e não tem mais tempo de execução ou tempo de quantum
        if (running_process != nullptr && (running_process->get_remaining_time() == 0 || time_slice_remaining_ == 0)) {
            if (running_process->get_remaining_time() == 0) {
                running_process->set_state("Finished");
                running_process->set_end(time);
                // Salva o contexto da CPU para o processo
                Context context = running_process->get_p_context();
                cpu->save_context(context);
            } else {
                running_process->set_state("Ready");
                ready_processes.push(running_process);
            }
            running_process = nullptr;
            time_slice_remaining_ = RR_QUANTUM;
        }

        // Verifica se o processador está livre e tem processo na fila
        if (running_process == nullptr && !ready_processes.empty()) {
            Process* next_process = ready_processes.front();
            ready_processes.pop();
             next_process->set_state("Running");
            next_process->set_begin(time);
            running_process = next_process;
            time_slice_remaining_ = RR_QUANTUM;
           // Carrega o contexto do processo para a CPU
            Context context = running_process->get_p_context();
            cpu->load_context(context);
        }

        // Processo executando
         // Processo executando
         if (running_process != nullptr && running_process->get_remaining_time() > 0){
            int remaining_time = running_process->get_remaining_time(); 
            remaining_time -= 1; // Subtrai 1 do tempo restante
            running_process->set_remaining_time(remaining_time);
            time_slice_remaining_ -= 1;
        }
    }


private:
    std::queue<Process*> ready_processes;   
    const int RR_QUANTUM = 2;
    int time_slice_remaining_;
};

#endif