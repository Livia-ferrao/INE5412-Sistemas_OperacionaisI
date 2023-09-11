
#include "process.h"

using namespace std;

Process::Process(int c, int d, int p, int pid) { 
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
}

Process::~Process() {
}

// Função que printa os atributos constantes do processo
ostream &operator<<(ostream& os, const Process& p) {
    os << p.id << " - Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << endl;
    return os;
}

// Função que printa os valores dos registradores do contexto do processo
void Process::print_process_context() {
    cout << "=========== PROCESS CONTEXT =============" << endl;
    cout << "- PC: " << p_context.get_pc() << endl;
    cout << "- SP: " << p_context.get_sp() << endl;
    cout << "- ST: " << p_context.get_st() << endl;
    for (int i = 0; i < 6; i++) {
        cout << "- REGISTER " << i << ": " << p_context.get_registers(i) << endl;
    }
}

int Process::get_id() const {
    return id;
}

void Process::set_id(int _id) {
    id = _id;
}

int Process::get_creation_time() const {
    return creation_time;
}

void Process::set_creation_time(int _creation_time) {
    creation_time = _creation_time;
}

int Process::get_duration() const {
    return duration;
}

void Process::set_duration(int _duration) {
    duration = _duration;
}

int Process::get_priority() const {
    return priority;
}

void Process::set_priority(int _priority) {
    priority = _priority;
}

int Process::get_waiting_time() const {
    return waiting_time;
}

void Process::set_waiting_time(int _waiting_time) {
    waiting_time = _waiting_time;
}

int Process::get_turnround_time() const {
    return turnround_time;
}

void Process::set_turnround_time(int _turnround_time) {
    turnround_time = _turnround_time;
}

int Process::get_remaining_time() const {
    return remaining_time;
}

void Process::set_remaining_time(int _remaining_time) {
    remaining_time = _remaining_time;
}

int Process::get_begin() const {
    return begin;
}

void Process::set_begin(int _begin) {
    begin = _begin;
}

int Process::get_end() const {
    return end;
}

void Process::set_end(int _end) {
    end = _end;
}

string Process::get_state() const {
    return state;
}

void Process::set_state(const string& _state) {
    state = _state;
}

Context Process::get_p_context() {
    return p_context;
}

void Process::set_p_context(const Context& _p_context) {
    p_context = _p_context;
}