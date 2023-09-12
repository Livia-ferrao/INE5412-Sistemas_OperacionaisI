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

    static void print_CPU_context();
    static void load_context(Context* p_context);
    static void save_context(Context* p_context);
    static int get_count_change_context();

private:
    static Context cpu_context;
    static int count_change_context;
};

#endif
