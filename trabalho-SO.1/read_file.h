#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#include "process.h"
using namespace std;

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

	void print_processes_params() {
		vector<Process *>::iterator iter = processes.begin();

		for(iter; iter < processes.end(); iter++) {
			Process *p = *iter;
			cout << *p;
		}
	}

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