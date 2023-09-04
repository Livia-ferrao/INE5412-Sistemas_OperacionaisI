#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


class Context {
    public:
        Context saveContext() {
            // Salvar o contexto do processo
            Context context;
            for (int i = 0; i < 6; i++) {
                context.registers[i] = registers[i];
            }
            context.SP = SP;
            context.PC = PC;
            context.ST = ST;
            return context;
        }

        void restoreContext(const Context& context) {
            // Restaurar o contexto do processo
            for (int i = 0; i < 6; i++) {
                registers[i] = context.registers[i];
            }
            SP = context.SP;
            PC = context.PC;
            ST = context.ST;
        }

    private:
        uint64_t registers[6];
        uint64_t SP;
        uint64_t PC;
        uint64_t ST;
};

class CPU {
    public:
        int switch_context(Context *from, Context *to);
};

class Process
{
public:
	Process(int c, int d, int p, int pid) { 
		creation_time = c;
		duration = d;
		priority = p;
        waiting_time = -1;
        turnround_time = -1;
        remaining_time = d;

        id = pid;
        begin = -1;
        end = -1;
        state = "New";
	}

	friend ostream &operator<<(ostream& os, const Process& p) {
		os << p.id << " - Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << endl;
		return os;
	}
	
public:	
	int creation_time; // at (arrival time)
	int duration; // bt (burst time)
	int priority;
    int waiting_time;
    int turnround_time;
    int remaining_time;

    int id;
    int begin;
    int end;  // ct (complete time) 
    string state;
    int total_exec_time;
    int quantum_exec_time;

    Context* context;
    static Process* running;
    static int active_processes;
};

class File
{

public:
	File() {
		myfile.open("entrada.txt");
		if (!myfile.is_open()) {
			cout << "Erro ao abrir o arquivo!\n";
		}
	}
	
	void read_file() {
	
		int a, b, c;
        int id = 0;
		
		if (!myfile.is_open()) {
			cout << "Arquivo não está aberto!" << endl;
		}
		
		while (myfile >> a >> b >> c) {
			Process *p = new Process(a, b, c, id);
			processes.push_back(p);
            id++;
		}

		cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
	}

	// void print_processes_params() {
	// 	vector<Process *>::iterator iter = processes.begin();

	// 	for(iter; iter < processes.end(); iter++) {
	// 		// cout << **processes.end();
	// 		// cout << **iter;
	// 		Process *p = *iter;
	// 		cout << *p;
	// 	}
	// }

	~File() {
		for(int i = 0; i < processes.size() ; i++) {
			Process *p = processes[i];
			delete p;
		}
	}

    vector<Process *>& getProcesses() {
        return processes;
    }

private:
	ifstream myfile; 
	vector<Process *> processes;
};


int FCFS(vector<Process*> p, int n)
{
    int i,j;
    int flag = 0,time = 0;
    float avgtat = 0,avgwt = 0;

    // for (Process *p : p) {
    //     cout << *p <<endl;
    // }

    for(i=0; i<n; i++)
    {   
        cout << "CONTEXTO-PROCESSO: " << p[i]->id << endl;
        p[i]->state = "Running";
        cout << "ESTADO: " << p[i]->state << endl;

        if(flag < p[i]->creation_time)
        {
            time = p[i]->creation_time - flag;
        }

        flag += p[i]->duration + time;
        time = 0;

        p[i]->end = flag;
        p[i]->turnround_time =  p[i]->end -  p[i]->creation_time;
        avgtat = avgtat + p[i]->turnround_time;
        p[i]->waiting_time = p[i]->turnround_time - p[i]->duration;
        avgwt = avgwt + p[i]->waiting_time;

        cout << "CONTEXTO: " << p[i]->id << endl;
        p[i]->state = "Waiting";
        cout << "ESTADO: " << p[i]->state << endl << endl;
    }

    printf("Table\n");
    printf("  AT BT CT TAT WT\n");

    for(i=0; i<n; i++)
    {
        printf("P%d-%d %d %d %d %d\n",i+1,p[i]->creation_time, p[i]->duration, p[i]->end, p[i]->turnround_time, p[i]->waiting_time);
    }

    printf("AVGTAT=%f  and AVGWT=%f\n",avgtat/n,avgwt/n);


    // printf("tempo P1 P2 P3 P4\n");
    // int numSegundos = 14; // Substitua pelo tempo máximo de término (end)
    // string processStatus[4] = {"--", "--", "--", "--"}; // Inicializa o estado de todos os processos

    // for (int segundo = 0; segundo < numSegundos; segundo++) {
    //     printf("%d - ", segundo);
    
    //     for (int i = 0; i < n; i++) {
    //         // Verifica se o processo i está em execução neste segundo
    //         if (segundo >= p[i]->creation_time && segundo <= p[i]->end) {
    //             processStatus[i] = "##";
    //         } else {
    //             processStatus[i] = "--";
    //         }
            
    //         printf("%s ", processStatus[i].c_str());
    //     }
    
    //     printf("\n");
    // }   

    return 0;
}

// void fcfs(vector<Process*> p, int n) {
//     int current_time = 0, index = 0;

//     cout << "AT:CT\tPID\n";

//     while (index < n) {
//         if (p[index]->creation_time <= current_time) {
//             cout << current_time << ':' << (current_time += p[index]->duration)
//                  << '\t' << p[index]->id << '\n';
//             ++index;
//         } else {
//             cout << current_time << ':' << p[index]->creation_time << "\tNULL" << '\n';
//             current_time = p[index]->creation_time;
//         }
//     }
// }


// void SJF(vector<Process*> p, int n)
// {
//     int Bt[n], Ct[n];

//     for(int i = 0; i < n; i++) {
//         Bt[i] = p[i]->duration;
//     }
//     int count = 0;
//     int j = 0;

//     while(j < n)
//     {
//         int min = 1000, ind = -1;
//         for(int i = 0; i < n; i++)
//         {
//             if(Bt[i] == min)
//             {
//                 if(p[i]->creation_time < p[ind]->creation_time)
//                 ind = i;
//             }
            
//             else if(Bt[i] < min)
//             {
//                 if(p[i]->creation_time <= count)
//                 {
//                     min = Bt[i];
//                     ind = i;
//                 }
//             }
            
//         }
//         if(ind != -1)
//         {
//             Ct[ind] = p[ind]->duration + count;
//             count += p[ind]->duration;
//             j++;
//             Bt[ind] = 1001;
//         }
//         else {
//             count++;
//         }
//     }
    
//     int TAT[n], WT[n];
    
//     for(int i=0;i<n;i++)
//         TAT[i]=Ct[i]-Arr[i];
    
//     for(int i=0;i<n;i++)
//         WT[i]=TAT[i]-BT[i];
    
//     printf("\nProcess Table:\nPid\tAT\tBT\tCT\tTAT\tWT\n");
//     for(int i=0; i<n; i++)
//         printf("P%d\t%d\t%d\t%d\t%d\t%d\n",(i+1),Arr[i],BT[i],Ct[i],TAT[i],WT[i]);
    
//     float sum=0;
//     for(int i = 0 ; i < n; i++) {
//         sum+=(float)TAT[i];
//     }
//     printf("\nAverage TAT: %f",sum/n);
//     sum=0;
//     for(int i = 0; i < n; i++)
//         sum+=(float)WT[i];
//     printf("\nAverage WT: %f",sum/n);
// }

// Função para comparar dois processos com base no tempo de duração.
struct CompareProcesses {
    bool operator()(const Process* a, const Process* b) const {
        return a->duration > b->duration;
    }
};

int main()
{
	File f;
	f.read_file();
	// f.print_processes_params();

    // criar um scheduler
    // sc = new Scheduler()
    // scheduler.SJF()
    
    vector<Process*> processes = f.getProcesses();
    for (Process *p : processes) {
        cout << *p;
    }

    // FCFS
    int n = processes.size();
    bool allFinished;
    int change_context = 0;
    int tmax = 30; // Tempo máximo de simulação
    int t = 0; // Tempo atual
    // std::queue<Process*> ready_queue; // Fila de processos prontos
    std::priority_queue<Process*, std::vector<Process*>, CompareProcesses> ready_queue;

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

        //Ordenar a ready_queue com base na duração dos processos
        // std::priority_queue<Process*, std::vector<Process*>, CompareProcesses> ready_queue;

        // Verifica se o processador está livre
        if (running_task == nullptr && !ready_queue.empty()) {
            // Process* next_task = ready_queue.front();
            Process* next_task = ready_queue.top();
            // cout << "NEXT TASK: "<< *next_task;
            ready_queue.pop();
            next_task->state = "Running";
            next_task->begin = t;
            running_task = next_task;
            change_context++;
            // cout << running_task << "\n";
            // cout << next_task << "\n";
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

    // FCFS(processes, n);
}



// while (t < tmax) {
    //      // Verifica se tem processo em execução
    //     if (running_task != nullptr) {
    //         if (running_task->remaining_time == 0) {
    //             running_task->state = "Finished";
    //             running_task->end = t;
    //             running_task = nullptr;
    //         } else if (running_task->quantum_count == running_task->quantum) {
    //             running_task->state = "Ready";
    //             ready_queue.push(*running_task);
    //             running_task = nullptr;
    //         }
    //     }

    //     // Verifica se alguma tarefa inicia agora
    //     for (Process *task : processes) {
    //         if (task.arrival_time == t) {
    //             task.state = "Ready";
    //             ready_queue.push(task);
    //         }
    //     }

    //     // Verifica se o processador está livre
    //     if (running_task == nullptr && !ready_queue.empty()) {
    //         Task next_task = ready_queue.front();
    //         ready_queue.pop();
    //         next_task.state = "Running";
    //         next_task.begin = t;
    //         if (next_task.quantum_count == 0) {
    //             next_task.quantum_count = 1;
    //         }
    //         running_task = &next_task;
    //     }
    // }