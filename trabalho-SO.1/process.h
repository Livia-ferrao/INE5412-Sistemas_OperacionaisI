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

    // ~Process() {
    //     delete p_context;
    // }

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

    int get_id() const {
        return id;
    }

    void set_id(int _id) {
        id = _id;
    }

    int get_creation_time() const {
        return creation_time;
    }

    void set_creation_time(int _creation_time) {
        creation_time = _creation_time;
    }

    int get_duration() const {
        return duration;
    }

    void set_duration(int _duration) {
        duration = _duration;
    }

    int get_priority() const {
        return priority;
    }

    void set_priority(int _priority) {
        priority = _priority;
    }

    int get_waiting_time() const {
        return waiting_time;
    }

    void set_waiting_time(int _waiting_time) {
        waiting_time = _waiting_time;
    }

    int get_turnround_time() const {
        return turnround_time;
    }

    void set_turnround_time(int _turnround_time) {
        turnround_time = _turnround_time;
    }

    int get_remaining_time() const {
        return remaining_time;
    }

    void set_remaining_time(int _remaining_time) {
        remaining_time = _remaining_time;
    }

    int get_begin() const {
        return begin;
    }

    void set_begin(int _begin) {
        begin = _begin;
    }

    int get_end() const {
        return end;
    }

    void set_end(int _end) {
        end = _end;
    }

    string get_state() const {
        return state;
    }

    void set_state(const string& _state) {
        state = _state;
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
    // static int active_processes;

    Context* p_context;
};

#endif