#ifndef CPU_H
#define CPU_H

#include <list>
#include <random>
#include "context.cpp"
#include "memory.h"

class CPU {
public:
    CPU() {}

    ~CPU() {}

    // Simulates the CPU changing states as it executes a process.
    // void change_state() {
    //     std::random_device rd;
    //     std::mt19937 gen(rd());
    //     std::uniform_int_distribution<> dis(0, 100);

    //     for (int n = 0; n < 6; ++n) {
    //         registers[n] = dis(gen);
    //     }
    //     cpu_context.sp = dis(gen);
    //     cpu_context.pc = dis(gen);
    //     cpu_context.st = dis(gen);
    // }

    // Handles the preemption of a process.
    void switch_context(Context p_contex_running, Context p_contex_next) {

        save_context(p_contex_running);
        load_context(p_contex_next);
        count_change_context += 1;
    }

private:
    Context cpu_context;
     int count_change_context = 0;

    void load_context(Context p_context) {
        p_context.set_registers(cpu_context.get_registers());
        p_context.set_st(cpu_context.get_st());
        p_context.set_sp(cpu_context.get_sp());
        p_context.set_pc(cpu_context.get_pc());
    }

     void save_context(Context p_context) {
        cpu_context.set_registers(p_context.get_registers());
        cpu_context.set_sp(p_context.get_sp());
        cpu_context.set_st(p_context.get_st());
        cpu_context.set_pc(p_context.get_pc());
    }
};

#endif