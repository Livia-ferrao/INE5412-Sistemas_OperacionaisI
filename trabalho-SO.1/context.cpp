#ifndef CONTEXT_CPP
#define CONTEXT_CPP

#include <vector>
#include <cstdlib> 
using namespace std;

class Context {
public:
    Context() {
        registers = vector<int>(6);
        sp = 0;
        pc = 0;
        st = 0;
    }

    Context(vector<int> registers_, int sp_, int pc_, int st_) {
        registers = registers_;
        sp = sp_;
        pc = pc_;
        st = st_;
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

    vector<int> get_registers() {
        return registers;
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

    void set_registers(const vector<int>& registers_) {
        registers = registers_;
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
    vector<int> registers;
    int sp;
    int pc; 
    int st;
};

#endif 