#include <iostream>
#include "operating_system.h"

int main(){
    int scheduler_type;
    std::cout << "Digite o algoritmo de escalonamento (0 = FCFS, 1 = SJF, 2 = PNP, 3 = PP, 4 = RR): ";
    std::cin >> scheduler_type;

    Operating_system OS;    
    OS.execute(scheduler_type);

    return 0;
}


