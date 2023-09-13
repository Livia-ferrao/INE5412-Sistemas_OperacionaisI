#include "operating_system.h"

Operating_system::Operating_system() {
    scheduler = nullptr; 
    cpu = nullptr;
}

Operating_system::~Operating_system() {
    for (int i = 0; i < processes_queue.size(); i++) {
        Process* p = processes_queue[i];
        delete p;
    }
    delete scheduler;
    delete cpu;
}


// Le a entrada, inicializa os processos, a CPU, o escalonador e chama a execução do algoritmo
void Operating_system::execute(int scheduler_type) {
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

// Inicializa escalonador
Scheduler* Operating_system::init_scheduler(int scheduler_type) {
    switch (scheduler_type) {
    case 0:
        return new FCFS();
        break;
    case 1:
        return new SJF();
        break;
    case 2:
        return new PNP();
        break;
    case 3:
        return new PPP();
        break;
    case 4:
        return new RR();
        break;
    default:
        return new RR();
    }
}

// Cria novos procesos e adiciona na fila
void Operating_system::init_processes(vector<Process*> processes){
    for (const Process* process : processes) {
        Process* new_process = new Process(*process);
        processes_queue.push_back(new_process);     
    }
}

// Enquanto todos processos não estarem no estado Finished então execute o escalonador
void Operating_system::run_scheduler() {
    int time = 0;
    bool allFinished = false;

    while(!allFinished) {
        // Inicializa a fila do escalonador
        scheduler->init_ready_queue(processes_queue, time);

        // Processa o algoritmo selecionado
        scheduler->schedule(time, cpu);

        // Verifica término do escalonamento
        allFinished = verify_finished_scheduling();
        if (allFinished){
            cout << "Todos os processos estão no estado 'Finished'. Saindo do loop." << endl;
            break;
        }

        // Printa estado dos processos a cada segundo de tempo
        scheduler->print_state(processes_queue, time);
    
        // PARA VER O CONTEXTO DOS PROCESSOS E DA CPU A CADA SEGUNDO DE TEMPO DESCOMENTE ESTA LINHA
        // scheduler->print_context(cpu);

        ++time;
    }

    // Imprime métricas finais do algoritmo escolhido
    print_metrics();
    time = 0;
}

// Verificação de término
bool Operating_system::verify_finished_scheduling(){
    int allFinished = true;
    for (int i = 0; i < processes_queue.size(); i++) {
        if (processes_queue[i]->get_state() != "Finished") {
            allFinished = false;
            return allFinished;
        }
    }
    return allFinished;
}

// Imprimir na tela os atributos dos processos
void Operating_system::print_processes_queue(){
    for (int i = 0; i < processes_queue.size(); i++) {
        cout << "ID: " << processes_queue[i]->get_id() << endl;
        cout << "DURATION: " << processes_queue[i]->get_duration() << endl;
        cout << "CREATION TIME: " << processes_queue[i]->get_creation_time() << endl;
        //...
    }
}

// Imprimir na tela métricas finais de cada algoritmo de escalonamento
void Operating_system::print_metrics(){
    double avgtat = 0;
    double avgwt = 0;
    
    for (Process *p : processes_queue) {
        p->set_turnround_time(p->get_end() - p->get_creation_time());
        p->set_waiting_time(p->get_turnround_time() - p->get_duration());
        cout << "------------ PROCESSO " << p->get_id() + 1 << "------------";
        cout << "\nTurnround time = " << p->get_turnround_time();
        cout << "\nWaiting time = " << p->get_waiting_time();

        avgtat = avgtat + p->get_turnround_time();
        avgwt = avgwt + p->get_waiting_time();
        cout << "\n\n";
    }

    cout << "\nTempo médio de Turnround time = " << avgtat/processes_queue.size();
    cout << "\nTempo médio de Waiting Time = " << avgwt/processes_queue.size();
    cout << "\nTrocas de contexto = " << cpu->get_count_change_context();
    cout << "\n";
}