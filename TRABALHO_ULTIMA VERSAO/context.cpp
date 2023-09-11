#ifndef CONTEXT_CPP
#define CONTEXT_CPP

#include "context.h"

class Context {
public:
    // Construtor
    Context() {
        for (int i = 0; i < 6; ++i) {
            registers[i] = 0;
        }
        sp = 0;
        pc = 0;
        st = 0;
    }

     // Destrutor
    ~Context() {}

    // Gera valores aleatórios para os registradores para simular a troca de contexto
    void generate_random_values(){
        for (int i = 0; i < 6; ++i) {
            registers[i] = rand();
        }
        pc = rand();
        st = rand();
        sp = rand();
    }

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