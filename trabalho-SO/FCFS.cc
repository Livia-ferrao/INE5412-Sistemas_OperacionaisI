#include "FCFS.h"

void FCFS::calculate(std::vector<Process*> processes)
{
    int n = processes.size();
    bool allFinished;
    int change_context = 0;
    int tmax = 30; // Tempo máximo de simulação
    int t = 0; // Tempo atual
    std::queue<Process*> ready_queue; // Fila de processos prontos

    Process* running_task = nullptr; // Processo em execução

    printf("\ntempo\t P1  P2  P3  P4\n");
    while (t < tmax) {
         // Verifica se tem processo em execução
        if (running_task != nullptr) {
            if (running_task->remaining_time == 0) {
                running_task->state = "Finished";
                running_task->end = t;
                running_task = nullptr;
            }
        }

        // Verifica se alguma tarefa inicia agora
        for (Process *task : processes) {
            if (task->creation_time == t) {
                task->state = "Ready";
                ready_queue.push(task);
            }
        }

        // Verifica se o processador está livre
        if (running_task == nullptr && !ready_queue.empty()) {
            Process* next_task = ready_queue.front();
            ready_queue.pop();
            next_task->state = "Running";
            next_task->begin = t;
            running_task = next_task;
            change_context++;
        }

        // Processo executando
        if (running_task != nullptr && running_task->remaining_time > 0){
            running_task->remaining_time -= 1;
        }

        // Verifique se todos processos já se encerraram
        allFinished = true;
        for (int i = 0; i < n; i++) {
            if (processes[i]->state != "Finished") {
                allFinished = false; // Se qualquer processo não estiver Finished, defina a variável como false
                break; // Saia do loop imediatamente, não é necessário continuar verificando
            }
        }
        if (allFinished) {
            cout << "Todos os processos estão no estado 'Finished'. Saindo do loop." << endl;
            break;
        }

        // Print table
        cout << t << "-" << t+1 << "\t";
        for (int i = 0; i < n; i++) {
            if (processes[i]->state != "Finished") {
                allFinished = false; // Se qualquer processo não estiver Finished, defina a variável como false
            }
            if (processes[i]->state == "Running"){
                 cout << "XX |"; 
            } else if(processes[i]->state == "Ready"){
                cout << "-- |";
            } else if(processes[i]->state == "Finished"){
                cout << "   |";
            } else {
                cout << "   |";
            }
        }

        cout << endl;
        // Incremento do tempo
        t++;
    }

    double avgtat = 0.0;
    double avgwt = 0.0;
    
    // Printa métricas
    for (Process *p : processes) {
        p->turnround_time =  p->end - p->creation_time;
        p->waiting_time = p->turnround_time - p->duration;
        printf("------------ PROCESSO %d ------------", p->id);
        printf("\nTurnround time = %d", p->turnround_time);
        printf("\nWaiting time = %d", p->waiting_time);

        avgtat = avgtat + p->turnround_time;
        avgwt = avgwt + p->waiting_time;
        printf("\n\n");
    }

     printf("\nTempo médio de Turnround time = %f",avgtat/n);
     printf("\nTempo médio de Waiting Time = %f\n", avgwt/n);
     printf("\nTrocas de contexto = %d\n", change_context);
}