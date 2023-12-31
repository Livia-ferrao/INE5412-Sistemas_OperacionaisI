#include <iostream>
#include "operating_system.h"

using namespace std;

int main(){
    int scheduler_type;
    cout << "0 - First Come, First Served\n";
    cout << "1 - Shortest Job First\n";
    cout << "2 - Priority Without Preemption\n";
    cout << "3 - Priority With Priority Preemption\n";
    cout << "4 - Round-Robin with Quantum\n";

    cout << "\n Digite o algoritmo de escalonamento: ";
    cin >> scheduler_type;

    Operating_system OS;    
    OS.execute(scheduler_type);

    return 0;
}
