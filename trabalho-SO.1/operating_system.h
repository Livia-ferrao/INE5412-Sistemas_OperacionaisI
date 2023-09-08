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
#include "SJF.h"
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

        // void create_processes(){
        //     for (const Process* process : processes_queue) {
        //         Process* new_process = new Process(*process); // Copie o objeto de processo
        //         new_processes_queue.push_back(new_process);      // Adicione à nova lista
        //     }
        //     time = 0;
        // }

        Scheduler* init_scheduler(int scheduler_type) {
            switch (scheduler_type)
            {
            case 0:
                // FCFS fcfs;  // Qual a diferença?
                return new FCFS();
                break;
            case 1:
                return new SJF();
                break;
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
            scheduler = init_scheduler(scheduler_type); // FCFS
            run_scheduler();
        }

        void run_scheduler() {
            bool allFinished = false;
            // create_processes();

            while(!allFinished) {

                scheduler->init_ready_queue(processes_queue, time);
                scheduler->processing(time);
                // cpu.switch_context();

                allFinished = verify_all_finished(allFinished);
                if (allFinished){
                    cout << "Todos os processos estão no estado 'Finished'. Saindo do loop." << endl;
                    break;
                }

                scheduler->print_state(processes_queue, time);

                ++time;
            }

            // scheduler.print_metrics();
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

        // colocar para escalonador e passar o processes_queue
        // void print_processes_state(){
        //     cout << time << "-" << time+1 << "\t";
        //     for (int i = 0; i < processes_queue.size(); i++) {
        //         if (processes_queue[i]->state == "Running"){
        //             cout << "XX |"; 
        //         } else if(processes_queue[i]->state == "Ready"){
        //             cout << "-- |";
        //         } else if(processes_queue[i]->state == "Finished"){
        //             cout << "   |";
        //         } else {
        //             cout << "   |";
        //         }
        //     }
        //     cout << endl;
        // }

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
        std::vector<Process *> new_processes_queue;
        Scheduler* scheduler;
        CPU cpu;
        int time;
};

#endif