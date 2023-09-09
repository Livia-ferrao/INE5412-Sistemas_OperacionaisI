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

        ~Operating_system(){
            for(int i = 0; i < processes_queue.size() ; i++) {
			    Process *p = processes_queue[i];
			    delete p;
		    }

            delete scheduler;
            delete cpu;
        }


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
                
                // PARA VER O CONTEXTO DOS PROCESSOS E DA CPU A CADA SEGUNDO DE TEMPO DESCOMENTE ESTA LINHA
                // scheduler->print_context();

                ++time;
            }
            print_metrics();
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

        void print_metrics(){
            int avgtat = 0;
            int avgwt = 0;
            for (Process *p : processes_queue) {
                p->turnround_time =  p->end - p->creation_time;
                p->waiting_time = p->turnround_time - p->duration;
                cout << "------------ PROCESSO " << p->id << "------------";
                cout << "\nTurnround time = " << p->turnround_time;
                cout << "\nWaiting time = " << p->waiting_time;

                avgtat = avgtat + p->turnround_time;
                avgwt = avgwt + p->waiting_time;
                cout << "\n\n";
            }

            cout << "\nTempo médio de Turnround time = " << avgtat/processes_queue.size();
            cout << "\nTempo médio de Waiting Time = " << avgwt/processes_queue.size();
            cout << "\nTrocas de contexto = " << cpu->get_count_change_context();
            cout << "\n";
        }

    private:
        std::vector<Process *> processes_queue;
        Scheduler* scheduler;
        CPU* cpu;
        int time;
};

#endif