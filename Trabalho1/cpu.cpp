#include <iostream>
#include "cpu.h"

// Construtor
CPU::CPU() {
    count_change_context = 0;
}

// Destrutor
CPU::~CPU() {
}

// Imprime na tela os valores dos registradores da CPU
void CPU::print_CPU_context() {
    std::cout << "=========== CPU CONTEXT =============" << std::endl;
    std::cout << "- PC: " << cpu_context.get_pc() << std::endl;
    std::cout << "- SP: " << cpu_context.get_sp() << std::endl;
    std::cout << "- ST: " << cpu_context.get_st() << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << "- REGISTER " << i << ": " << cpu_context.get_registers(i) << std::endl;
    }
}

// Salva o contexto do processo para os registradores da CPU
void CPU::load_context(Context* p_context) {
    // Gera valores aleatórios para os registradores dos processos
    p_context->generate_random_values();

    // Contagem da troca de contexto
    count_change_context += 1;

    for (int i = 0; i < 6; i++) {
        cpu_context.set_registers(i, p_context->get_registers(i));
    }
    cpu_context.set_sp(p_context->get_sp());
    cpu_context.set_st(p_context->get_st());
    cpu_context.set_pc(p_context->get_pc());
}

// Salva o contexto da CPU para os registradores dos processos
void CPU::save_context(Context* p_context) {
    for (int i = 0; i < 6; i++) {
        p_context->set_registers(i, cpu_context.get_registers(i));
    }
    p_context->set_st(cpu_context.get_st());
    p_context->set_sp(cpu_context.get_sp());
    p_context->set_pc(cpu_context.get_pc());
}

// GET count_change_context
int CPU::get_count_change_context() {
    return count_change_context;
}

void CPU::set_count_change_context(int count_change_context_) {
    count_change_context = count_change_context_;
}