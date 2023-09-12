#include "SJF.h"

void SJF::init_ready_queue(std::vector<Process*> processes, int time) {
    for (Process* process : processes) {
        if (process->get_creation_time() == time) {
            process->set_state("Ready");
            ready_processes.push(process);
        }
    }
}

void SJF::schedule(int time) {
    if (running_process != nullptr && running_process->get_remaining_time() == 0) {
        running_process->set_state("Finished");
        running_process->set_end(time);
        CPU::save_context(running_process->get_p_context());
        running_process = nullptr;
    }

    if (running_process == nullptr && !ready_processes.empty()) {
        Process* next_process = ready_processes.top();
        ready_processes.pop();
        next_process->set_state("Running");
        next_process->set_begin(time);
        running_process = next_process;
        CPU::load_context(running_process->get_p_context());
    }

    if (running_process != nullptr && running_process->get_remaining_time() > 0) {
        int remaining_time = running_process->get_remaining_time();
        remaining_time -= 1;
        running_process->set_remaining_time(remaining_time);
    }
}