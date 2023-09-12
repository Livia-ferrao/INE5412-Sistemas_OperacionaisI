#include "scheduler.h"

void Scheduler::print_context() {
    CPU::print_CPU_context();
    running_process->print_process_context();
}

void Scheduler::print_state(std::vector<Process*> processes_queue, int time) {
    std::cout << time << "-" << time+1 << "\t";
    int size = processes_queue.size();
    for (int i = 0; i < size; i++) {
        if (processes_queue[i]->get_state() == "Running") {
            std::cout << "XX |"; 
        } else if(processes_queue[i]->get_state() == "Ready") {
            std::cout << "-- |";
        } else if(processes_queue[i]->get_state() == "Finished") {
            std::cout << "   |";
        } else {
            std::cout << "   |";
        }
    }
    std::cout << std::endl;
}
