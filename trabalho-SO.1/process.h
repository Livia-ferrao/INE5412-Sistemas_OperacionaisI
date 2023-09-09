#ifndef PROCESS_CC
#define PROCESS_CC

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#include "context.cpp"

using namespace std;

class Process
{
public:
    Process() {};

	Process(int c, int d, int p, int pid) { 
        id = pid;
		creation_time = c;
		duration = d;
		priority = p;
        waiting_time = -1;
        turnround_time = -1;
        remaining_time = d;
        begin = -1;
        end = -1;
        state = "New";
        p_context = new Context();
	}

	friend ostream &operator<<(ostream& os, const Process& p) {
		os << p.id << " - Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << endl;
		return os;
	}

    void print_process_context(){
        cout << "=========== PROCESS CONTEXT =============" << endl;
        cout << "- PC: " << p_context->get_pc() << endl;
        cout << "- SP: " << p_context->get_sp() << endl;
        cout << "- ST: " << p_context->get_st() << endl;
        for (int i=0; i < 6; i++){
            cout << "- REGISTER " << i << ": " << p_context->get_registers(i) << endl;
        }
    }
	
public:	
    int id;
	int creation_time;
	int duration;
	int priority;
    int waiting_time;
    int turnround_time;
    int remaining_time;
    int begin;
    int end; 
    string state;
    // int total_exec_time;
    // int quantum_exec_time;
    // static Process* running;
    // static int active_processes;

    Context* p_context;
};

#endif