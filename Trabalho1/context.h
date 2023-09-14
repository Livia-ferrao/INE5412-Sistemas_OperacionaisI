#ifndef CONTEXT_H
#define CONTEXT_H

#include <cstdlib>
#include <iostream>

class Context {
public:
    Context();
    ~Context();

    void generate_random_values();
    int get_registers(int index);
    int get_sp();
    int get_pc();
    int get_st();
    void set_registers(int index, int value);
    void set_sp(int sp_);
    void set_pc(int pc_);
    void set_st(int st_);

private:
    int registers[6];
    int sp;
    int pc;
    int st;
};

#endif
