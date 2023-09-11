#ifndef PPP_H
#define PPP_H

#include <queue>
#include <vector>
#include "process.h"
#include "scheduler.h"

class PPP: public Scheduler {

public:

    // PPP(CPU* _cpu) : Scheduler(_cpu) {}

    PPP() {}

    ~PPP() {}

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
        //  Verifica se tem processo em execução e ainda tem tempo de execução
         if (running_process != nullptr && running_process->get_remaining_time() == 0) {
            running_process->set_state("Finished");
            running_process->set_end(time);
            // Salva o contexto da CPU para o processo
            Context context = running_process->get_p_context();
            cpu->save_context(context);
            running_process = nullptr;
        }

        if ((running_process == nullptr || running_process->get_priority() < ready_processes.top()->get_priority()) && !ready_processes.empty()) {
            if (running_process != nullptr) {
                // Preempção: atualize o estado do processo em execução e coloque-o de volta na fila de prontidão
                running_process->set_state("Ready");
                ready_processes.push(running_process);
            }
            // Selecione o próximo processo com maior prioridade
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
    struct CompareProcessesPriority {
        bool operator()(const Process* a, const Process* b) const {
            return a->get_priority() < b->get_priority(); // Comparação por prioridade
        }
    };
    std::priority_queue<Process*, std::vector<Process*>, CompareProcessesPriority> ready_processes;
};

#endif