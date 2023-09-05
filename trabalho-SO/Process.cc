#ifndef PROCESS_CC
#define PROCESS_CC

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

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

    static Process* running;
    static int active_processes;
};

#endif