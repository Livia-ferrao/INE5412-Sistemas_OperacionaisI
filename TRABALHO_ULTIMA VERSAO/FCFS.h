#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include "process.h"
#include "scheduler.h"

class FCFS: public Scheduler {

public:
    // Construtor
    // FCFS(CPU* _cpu) : Scheduler(_cpu) {}

    FCFS() {}

    // Destrutor
    ~FCFS(){
        cout << "ENTROU AQUI ============= " << endl;
        while (!ready_processes.empty()) {
            Process* process = ready_processes.front();  // Obtenha o próximo elemento da fila
            ready_processes.pop();  // Remova o elemento da fila
            delete process;  // Libere a memória do objeto Process
        }
    }

    // Verifica se alguma tarefa inicia agora e adiciona na fila
    void init_ready_queue(std::vector<Process*> processes, int time){
        for (Process *process : processes) {
            if (process->get_creation_time() == time) {
                process->set_state("Ready");
                ready_processes.push(process);
            }
        }

        // while (!ready_processes.empty()) {
        //     Process* process = ready_processes.front(); // Obtenha o próximo elemento da fila
        //     ready_processes.pop(); // Remova o elemento da cópia da fila
        //     // Imprima os valores do processo (ou apenas o que desejar)
        //     std::cout << "Process ID: " << process<< std::endl; // Substitua getId() pelo método correto para acessar os atributos do seu objeto Process
        // }
    }

    void processing(int time, CPU *cpu) {
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
            Process* next_process = ready_processes.front();
            cout << next_process << endl;
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
    std::queue<Process*> ready_processes;
};

#endif