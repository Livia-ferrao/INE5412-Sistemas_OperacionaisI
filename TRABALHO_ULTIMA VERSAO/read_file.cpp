
#include "read_file.h"

File::File() {
    myfile.open("entrada.txt");
    if (!myfile.is_open()) {
        std::cout << "Erro ao abrir o arquivo!\n";
    }
}

void File::read_file() {
    int a, b, c;
    int id = 0;

    if (!myfile.is_open()) {
        std::cout << "Arquivo não está aberto!" << std::endl;
    }

    while (myfile >> a >> b >> c) {
        Process* p = new Process(a, b, c, id);
        processes.push_back(p);
        id++;
    }

    std::cout << "Quantidade de processos lidos do arquivo: " << processes.size() << std::endl;
}

void File::print_processes_params() {
    std::vector<Process*>::iterator iter = processes.begin();

    for (iter; iter < processes.end(); iter++) {
        Process* p = *iter;
        std::cout << *p;
    }
}

File::~File() {
    for (int i = 0; i < processes.size(); i++) {
        Process* p = processes[i];
        delete p;
    }
}

std::vector<Process*>& File::getProcesses() {
    return processes;
}