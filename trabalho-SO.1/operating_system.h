#ifndef OPERATING_SYSTEM_CC
#define OPERATING_SYSTEM_CC

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#include "read_file.h"
#include "process.h"
#include "scheduler.h"
#include "cpu.cpp"
#include "FCFS.h"
#include "SJF.h"
#include "PNP.h"
#include "PPP.h"
#include "RR.h"
// #include "constantes.h"


class Operating_system {
    
    vector<Process*> process;

    public:
        Operating_system() {
            // std::cout << "Lendo arquivo\n";
            // File f;
            // f.read_file();
            // f.print_processes_params();
            // vector<Process*> processes = f.getProcesses();
            // processes_queue = processes;
            
            // // Crie uma cópia profunda dos objetos de processo
            // for (const Process* process : processes) {
            //     Process* new_process = new Process(*process); // Copie o objeto de processo
            //     processes_queue.push_back(new_process);      // Adicione à nova lista
            // }

            scheduler = nullptr;
            time = 0;
        }

        ~Operating_system(){}


        Scheduler* init_scheduler(int scheduler_type) {
            switch (scheduler_type)
            {
            case 0:
                return new FCFS(cpu);
                break;
            case 1:
                return new SJF(cpu);
                break;
            case 2:
                return new PNP(cpu);
                break;
            case 3:
                return new PPP(cpu);
                break;
            case 4:
                return new RR(cpu);
                break;
            default:
                return new FCFS(cpu);
            }
        }

        void init_processes(vector<Process*> processes){
            for (const Process* process : processes) {
                Process* new_process = new Process(*process); // Copie o objeto de processo
                processes_queue.push_back(new_process);      // Adicione à nova lista
            }
        }

        void execute(int scheduler_type) {
            std::cout << "Lendo arquivo\n";
            File f;
            f.read_file();
            f.print_processes_params();
            vector<Process*> processes = f.getProcesses();
            init_processes(processes);
            cpu = new CPU();
            scheduler = init_scheduler(scheduler_type); // FCFS, SJF, RR...
            run_scheduler();
        }

        void run_scheduler() {
            bool allFinished = false;

            while(!allFinished) {

                scheduler->init_ready_queue(processes_queue, time);
                scheduler->processing(time);

                allFinished = verify_all_finished(allFinished);
                if (allFinished){
                    cout << "Todos os processos estão no estado 'Finished'. Saindo do loop." << endl;
                    break;
                }

                scheduler->print_state(processes_queue, time);

                ++time;
            }

            // scheduler->print_metrics();
            time = 0;
        }

        bool verify_all_finished(int allFinished){
            allFinished = true;
            for (int i = 0; i < processes_queue.size(); i++) {
                if (processes_queue[i]->state != "Finished") {
                    allFinished = false; // Se qualquer processo não estiver Finished, defina a variável como false
                    return allFinished;
                }
            }
            return allFinished;
        }

        void print_processes_queue(){
            for (int i = 0; i < processes_queue.size(); i++) {
                cout << "ID: " << processes_queue[i]->id << endl;
                cout << "DURATION: " << processes_queue[i]->duration << endl;
                cout << "CREATION TIME: " << processes_queue[i]->creation_time << endl;
                //...
            }
        }

    private:
        std::vector<Process *> processes_queue;
        Scheduler* scheduler;
        CPU* cpu;
        int time;
};

#endif