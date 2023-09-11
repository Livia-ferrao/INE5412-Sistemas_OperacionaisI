#ifndef CPU_CPP
#define CPU_CPP

#include "cpu.h"

class CPU {
public:
    // Construtor
    CPU() {
        count_change_context = 0;
    }

    // Destrutor
    ~CPU() {
    }

    // Imprime na rela os valores dos regisradores da CPU
    void print_CPU_context(){
        cout << "=========== CPU CONTEXT =============" << endl;
        cout << "- PC: " << cpu_context.get_pc() << endl;
        cout << "- SP: " << cpu_context.get_sp() << endl;
        cout << "- ST: " << cpu_context.get_st() << endl;
        for (int i=0; i < 6; i++){
            cout << "- REGISTER " << i << ": " << cpu_context.get_registers(i) << endl;
        }
    }

    // Salva o contexto do processo para os registradores da CPU
    void load_context(Context& p_context) {
        // Gera valores aleatórios para os registradores dos processos
        p_context.generate_random_values();

        // Contagem da troca de contexto
        count_change_context += 1;

        for (int i=0; i < 6; i++){
            cpu_context.set_registers(i, p_context.get_registers(i));
        }
        cpu_context.set_sp(p_context.get_sp());
        cpu_context.set_st(p_context.get_st());
        cpu_context.set_pc(p_context.get_pc());
    }

    // Salva o contexto da CPU para os registradores dos processos
     void save_context(Context& p_context) {
        for (int i=0; i < 6; i++){
            p_context.set_registers(i, cpu_context.get_registers(i));
        }
        p_context.set_st(cpu_context.get_st());
        p_context.set_sp(cpu_context.get_sp());
        p_context.set_pc(cpu_context.get_pc());
    }

    int get_count_change_context() {
        return count_change_context;
    }

private:
    Context cpu_context;
    int count_change_context;
};

#endif