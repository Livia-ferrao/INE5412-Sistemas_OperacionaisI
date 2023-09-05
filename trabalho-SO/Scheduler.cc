#include "FCFS.h"
#include "SJF.h"
#include "Process.cc"

class Scheduler {
public:
    Scheduler(std::vector<Process*> processes){
        queue_processes = processes;
        // Inicialize os objetos de algoritmo de escalonamento
        // fcfs_ = new FCFS(processes_);
        // sjf_ = new SJF(processes_);
    }


     void executeAlgorithm(const std::string& algorithm) {
        if (algorithm == "FCFS") {
            FCFS fcfs;
            fcfs.calculate(queue_processes); // Execute o algoritmo FCFS
        } else if (algorithm == "SJF") {
            SJF sjf;
            sjf.calculate(queue_processes); // Execute o algoritmo SJF
        } else {
            std::cout << "Algoritmo de escalonamento não reconhecido." << std::endl;
        }
    }

private:
    std::vector<Process*> queue_processes;
};