
#include "context.h"

// Coonstrutor
Context::Context() {
    for (int i = 0; i < 6; ++i) {
        registers[i] = 0;
    }
    sp = 0;
    pc = 0;
    st = 0;
}

// Destrutor
Context::~Context() {}

// Gera valores aleatórios para os registradores
void Context::generate_random_values() {
    for (int i = 0; i < 6; ++i) {
        registers[i] = rand();
    }
    pc = rand();
    st = rand();
    sp = rand();
}

int Context::get_registers(int index) {
    return registers[index];
}

int Context::get_sp() {
    return sp;
}

int Context::get_pc() {
    return pc;
}

int Context::get_st() {
    return st;
}

void Context::set_registers(int index, int value) {
    registers[index] = value;
}

void Context::set_sp(int sp_) {
    sp = sp_;
}

void Context::set_pc(int pc_) {
    pc = pc_;
}

void Context::set_st(int st_) {
    st = st_;
}