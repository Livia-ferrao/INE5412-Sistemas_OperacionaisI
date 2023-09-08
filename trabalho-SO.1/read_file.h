#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "process.h"
using namespace std;

// class Process
// {
// public:
//     Process(int c, int d, int p) : creation_time(c), duration(d), priority(p) {}

//     friend ostream &operator<<(ostream &os, const Process &p)
//     {
//         os << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << endl;
//         return os;
//     }

// private:
//     int creation_time;
//     int duration; //seconds
//     int priority;
// };

class File
{
public:
    File() {
        myfile.open("entrada.txt");
        if (!myfile.is_open()) {
            cout << "Erro ao abrir o arquivo!\n";
        }
    }

    void read_file();

    void print_processes_params();

	vector<Process *>& getProcesses() {
        return processes;
    }

    ~File() {
        for (int i = 0; i < processes.size(); i++) {
            Process *p = processes[i];
            delete p;
        }
    }

private:
    ifstream myfile;
    vector<Process *> processes;
};