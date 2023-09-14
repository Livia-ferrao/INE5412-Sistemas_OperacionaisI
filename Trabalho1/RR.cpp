#include "RR.h"

void RR::init_ready_queue(std::vector<Process*> processes, int time) {
    for (Process* process : processes) {
        if (process->get_creation_time() == time) {
            process->set_state("Ready");
            ready_processes.push(process);
        }
    }
}

void RR::schedule(int time, CPU* cpu) {
    if (running_process != nullptr && (running_process->get_remaining_time() == 0 || time_slice_remaining_ == 0)) {
        if (running_process->get_remaining_time() == 0) {
            running_process->set_state("Finished");
            running_process->set_end(time);
            cpu->save_context(running_process->get_p_context());
        } else {
            running_process->set_state("Ready");
            ready_processes.push(running_process);
        }
        running_process = nullptr;
        time_slice_remaining_ = RR_QUANTUM;
    }

    if (running_process == nullptr && !ready_processes.empty()) {
        Process* next_process = ready_processes.front();
        ready_processes.pop();
        next_process->set_state("Running");
        next_process->set_begin(time);
        running_process = next_process;
        time_slice_remaining_ = RR_QUANTUM;
        cpu->load_context(running_process->get_p_context());
    }

    if (running_process != nullptr && running_process->get_remaining_time() > 0) {
        int remaining_time = running_process->get_remaining_time();
        remaining_time -= 1;
        running_process->set_remaining_time(remaining_time);
        time_slice_remaining_ -= 1;
    }
}