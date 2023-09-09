#ifndef CONTEXT_CPP
#define CONTEXT_CPP

#include <vector>
#include <cstdlib> 
#include <ctime>
#include <random>
#include <iostream>
using namespace std;

class Context {
public:
    Context() {
        for (int i = 0; i < 6; ++i) {
            registers[i] = 0;
        }
        sp = 0;
        pc = 0;
        st = 0;
    }

    void generate_random_values(){
        for (int i = 0; i < 6; ++i) {
            registers[i] = rand(); // Atribui um novo valor aleatório ao registrador
        }
        pc = rand();
        st = rand();
        sp = rand();
    }

    ~Context() {}

    int get_registers(int index) {
        return registers[index];
    }

    int get_sp()  {
        return sp;
    }

    int get_pc() {
        return pc;
    }

    int get_st() {
        return st;
    }

    void set_registers(int index, int value) {
        registers[index] = value;
    }

    void set_sp(int sp_){
        sp = sp_;
    }

    void set_pc(int pc_){
        pc = pc_;
    }

    void set_st(int st_){
        st = st_;
    }


private:
    int registers[6];
    int sp;
    int pc; 
    int st;
};

#endif 