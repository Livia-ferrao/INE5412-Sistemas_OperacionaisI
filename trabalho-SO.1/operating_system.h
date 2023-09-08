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
#include "FCFS.h"
#include "scheduler.h"
#include "cpu.cpp"
// #include "constantes.h"


class Operating_system {
    public:
        Operating_system() {
            std::cout << "Lendo arquivo\n";
            File f;
            f.read_file();
            f.print_processes_params();
            vector<Process*> processes = f.getProcesses();
            // processes_queue = processes;

            // Crie uma cópia profunda dos objetos de processo
            for (const Process* process : processes) {
                Process* new_process = new Process(*process); // Copie o objeto de processo
                processes_queue.push_back(new_process);      // Adicione à nova lista
            }
            time = 0;
        }

        Scheduler* create_scheduler(int scheduler_type) {
            switch (scheduler_type)
            {
            case 0:
                // FCFS fcfs;  // Qual a diferença?
                return new FCFS();
                break;
            // case 1:
            //     // return SJFScheduler();
            //     break;
            // case 2:
            //     // return PNPScheduler();
            //     break;
            // case 3:
            //     // return PPScheduler();
            //     break;
            // case 4:
            //     // return RRNPScheduler();
            //     break;
            default:
                return new FCFS();
            }
        }

        void execute(int scheduler_type) {
            scheduler = create_scheduler(scheduler_type); // FCFS
            // run_scheduler();
        }

        void run_scheduler() {
            printf("entrou\n");
            bool allFinished = true;
            while(allFinished) {

                 for (int i = 0; i < processes_queue.size(); i++) {
                    cout << processes_queue[i]->duration << endl;
                    cout << processes_queue[i]->creation_time << endl;
                }   

                scheduler->init_ready_queue(processes_queue, time);
                scheduler->processing();
                // scheduler.finish_processing();
                // cpu.switch_context();

                allFinished = verify_all_finished(allFinished);
                if (allFinished){
                    cout << "Todos os processos estão no estado 'Finished'. Saindo do loop." << endl;
                    break;
                }
                print_processes_state();
                ++time;
            }

            // scheduler.print_metrics();
            allFinished = false;
        }

        bool verify_all_finished(int allFinished){
            allFinished = true;
            for (int i = 0; i < processes_queue.size(); i++) {
                if (processes_queue[i]->state != "Finished") {
                    return allFinished = false; // Se qualquer processo não estiver Finished, defina a variável como false
                }
            }
            return allFinished;
        }

        void print_processes_state(){
            cout << time << "-" << time+1 << "\t";
            for (int i = 0; i < processes_queue.size(); i++) {
                if (processes_queue[i]->state == "Running"){
                    cout << "XX |"; 
                } else if(processes_queue[i]->state == "Ready"){
                    cout << "-- |";
                } else if(processes_queue[i]->state == "Finished"){
                    cout << "   |";
                } else {
                    cout << "   |";
                }
            }
        }

        void print_processes_queue(){
            for (int i = 0; i < processes_queue.size(); i++) {
                cout << "ID: " << processes_queue[i]->id << endl;
                cout << "DURATION: " << processes_queue[i]->duration << endl;
                cout << "CREATION TIME: " << processes_queue[i]->duration << endl;
            }
        }

    private:
        std::vector<Process *> processes_queue;
        Scheduler* scheduler;
        CPU cpu;
        int time;
};

#endif