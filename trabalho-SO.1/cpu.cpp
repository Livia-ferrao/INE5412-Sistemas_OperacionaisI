#ifndef CPU_H
#define CPU_H

#include <list>
#include <random>
#include <iostream> 
#include "context.cpp"

class CPU {
public:
    CPU() {
        // cpu_context = new Context();
        count_change_context = 0;
    }

    ~CPU() {}

    // void print_CPU_context(){
    //     cout << "CPU_CONTEXT - PC: " << cpu_context->get_pc();
    //     cout << "CPU_CONTEXT - SP: " << cpu_context->get_pc();
    //     cout << "CPU_CONTEXT - ST: " << cpu_context->get_pc();
    //     for (int i=0; i<cpu_context->get_registers().size(); i++){
    //         cout << "CPU_CONTEXT - REGISTERS " << i << cpu_context->get_registers()[i];
    //     }
    // }

    void load_context(Context* p_context) {
        p_context->set_registers(cpu_context->get_registers());
        p_context->set_st(cpu_context->get_st());
        p_context->set_sp(cpu_context->get_sp());
        p_context->set_pc(cpu_context->get_pc());
    }

     void save_context(Context* p_context) {
        // Generate random values for de processes registers
        p_context->generate_random_values();
        cpu_context->set_registers(p_context->get_registers());
        cpu_context->set_sp(p_context->get_sp());
        cpu_context->set_st(p_context->get_st());
        cpu_context->set_pc(p_context->get_pc());
    }

    void switch_context(Context* p_contex_running, Context* p_contex_next) {
        save_context(p_contex_running);
        load_context(p_contex_next);
        count_change_context += 1;
    }

private:
    Context* cpu_context = nullptr;
    int count_change_context ;
};

#endif