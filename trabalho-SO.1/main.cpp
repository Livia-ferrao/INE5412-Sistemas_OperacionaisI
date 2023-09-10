#include <iostream>
#include "operating_system.h"

using namespace std;

int main(){
    int scheduler_type;
    Operating_system OS; 
    
    // Executar FCFS
    scheduler_type = 0;
    OS.execute(scheduler_type);

    // Executar SJF
    scheduler_type = 1;
    OS.execute(scheduler_type);

    // Executar PNP
    scheduler_type = 2;
    OS.execute(scheduler_type);

    // Executar PPP
    scheduler_type = 3;
    OS.execute(scheduler_type);

    // Executar RR
    scheduler_type = 4;
    OS.execute(scheduler_type);

    return 0;
}


