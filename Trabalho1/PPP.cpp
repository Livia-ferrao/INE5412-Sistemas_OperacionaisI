#include "PPP.h"

// Verifica se alguma tarefa inicia agora e adiciona na fila
void PPP::init_ready_queue(std::vector<Process*> processes, int time) {
    for (Process* process : processes) {
        if (process->get_creation_time() == time) {
            process->set_state("Ready");
            ready_processes.push(process);
        }
    }
}

// Realiza o escalonamento
void PPP::schedule(int time, CPU* cpu) {
    //  Verifica se tem processo em execução e o tempo de execução terminou
    if (running_process != nullptr && running_process->get_remaining_time() == 0) {
        running_process->set_state("Finished");
        running_process->set_end(time);
        // Salva o contexto da CPU para o processo
        cpu->save_context(running_process->get_p_context());
        running_process = nullptr;
    }

    // Verifica se não tem processo em execução no momento ou tem processo com mais prioridade na fila e se tem processo na fila
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
        cpu->load_context(running_process->get_p_context());
    }

     // Processo executando
    if (running_process != nullptr && running_process->get_remaining_time() > 0){
        int remaining_time = running_process->get_remaining_time(); 
        remaining_time -= 1; // Subtrai 1 do tempo restante
        running_process->set_remaining_time(remaining_time);
    }
}