#ifndef OPERATING_SYSTEM_H
#define OPERATING_SYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#include "process.h"
#include "scheduler.h"
#include "cpu.cpp"
// #include "constantes.h"
using namespace std;


class Operating_system {

    public:
        Operating_system();

        ~Operating_system();

        void execute(int scheduler_type);                 

        // Imprimir na tela métricas finais de cada algoritmo de escalonamento
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
        Scheduler* init_scheduler(int scheduler_type);
        void init_processes(vector<Process*> processes);
        void print_processes_queue();
        bool verify_all_finished(int allFinished);
        void run_scheduler(); 
        
        vector<Process *> processes_queue;
        Scheduler* scheduler;
        CPU* cpu;
};

#endif