#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include "Operating_system.h"
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
using namespace std;


Operating_system::Operating_system() {
    scheduler = nullptr;
    time = 0; 

    // cout << "Lendo arquivo\n";

    // File f;
    // f.read_file();
    // f.print_processes_params();
    
    // vector<Process*> processes = f.getProcesses();
    // processes_queue = f.getProcesses();
    
    
    //init_processes(processes);
    print_processes_queue();   
    
}

Operating_system::~Operating_system() {
    // Libere a memória alocada para os processos, scheduler e cpu
    for (Process* p : processes_queue) {
        delete p;
    }
    delete scheduler;
    delete cpu;
}

Scheduler* Operating_system::init_scheduler(int scheduler_type) {
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
        return nullptr;
    }
}

void Operating_system::init_processes(vector<Process*> processes){
    for (const Process* process : processes) {
        Process* new_process = new Process(*process); // Copie o objeto de processo
        //processes_queue.push_back(new_process);      // Adicione à nova lista
    }
}

void Operating_system::execute(int scheduler_type) {
    // cout << "Lendo arquivo\n";
    cout << "Executando com o algoritmo " << scheduler_type << endl;

    File f;
    f.read_file();
    f.print_processes_params();
    
    vector<Process*> processes = f.getProcesses();
    processes_queue = processes;
    
    print_processes_queue();
    //init_processes(processes_queue);
    // print_processes_queue();

    cpu = new CPU();
    scheduler = init_scheduler(scheduler_type); // FCFS, SJF, RR...

    run_scheduler();
    
   

}

void Operating_system::run_scheduler() {
    print_processes_queue();
    
    bool allFinished = false;

    while(!allFinished) {

        scheduler->init_ready_queue(processes_queue, time);
        scheduler->processing(time);

        allFinished = verify_all_finished(allFinished);
        if (allFinished){
            cout << "Todos os processos estao no estado 'Finished'. Saindo do loop." << endl;
            break;
        }

        scheduler->print_state(processes_queue, time);

        ++time;
    }
    scheduler->print_metrics();
    time = 0;
}

bool Operating_system::verify_all_finished(int allFinished){
    allFinished = true;
    for (int i = 0; i < processes_queue.size(); i++) {
        if (processes_queue[i]->state != "Finished") {
            allFinished = false; // Se qualquer processo não estiver Finished, defina a variável como false
            return allFinished;
        }
    }
    return allFinished;
}

void Operating_system::print_processes_queue(){
    cout << "\nProcess queue: \n";
    for (int i = 0; i < processes_queue.size(); i++) {
        cout << "ID: " << processes_queue[i]->id << endl;
        cout << "DURATION: " << processes_queue[i]->duration << endl;
        cout << "CREATION TIME: " << processes_queue[i]->creation_time << endl;
    }
}

