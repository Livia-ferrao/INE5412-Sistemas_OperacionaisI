#ifndef CPU_H
#define CPU_H

#include <list>
#include <random>
#include <iostream> 
#include "context.h"

class CPU {
public:
    CPU();
    ~CPU();

    void print_CPU_context();
    void load_context(Context* p_context);
    void save_context(Context* p_context);
    int get_count_change_context();

private:
    Context cpu_context;
    int count_change_context;
};

#endif
