#include "SJF.h"

// Verifica se alguma tarefa inicia agora e adiciona na fila
void SJF::init_ready_queue(std::vector<Process*> processes, int time) {
    for (Process* process : processes) {
        if (process->get_creation_time() == time) {
            process->set_state("Ready");
            ready_processes.push(process);
        }
    }
}

// Realiza o escalonamento
void SJF::schedule(int time, CPU* cpu) {
     //  Verifica se tem processo em execução e o tempo de execução terminou
    if (running_process != nullptr && running_process->get_remaining_time() == 0) {
        running_process->set_state("Finished");
        running_process->set_end(time);
         // Salva o contexto da CPU para o processo
        cpu->save_context(running_process->get_p_context());
        running_process = nullptr;
    }

    // Verifica se não tem processo em execução no momento e se tem processo na fila
    if (running_process == nullptr && !ready_processes.empty()) {
        Process* next_process = ready_processes.top();
        ready_processes.pop();
        next_process->set_state("Running");
        next_process->set_begin(time);
        running_process = next_process;
        cpu->load_context(running_process->get_p_context());
    }

    // Processo executando
    if (running_process != nullptr && running_process->get_remaining_time() > 0) {
        int remaining_time = running_process->get_remaining_time();
        remaining_time -= 1; // Subtrai 1 do tempo restante
        running_process->set_remaining_time(remaining_time);
    }
}