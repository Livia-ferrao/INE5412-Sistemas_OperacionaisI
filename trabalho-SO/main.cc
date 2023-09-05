#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

#include "FCFS.h"
#include "SJF.h"
#include "read_file.cc"
#include "Process.cc"
#include "Scheduler.cc"

int main()
{
    File f;
	f.read_file();
	f.print_processes_params();

    vector<Process*> processes = f.getProcesses();

    Scheduler scheduler(processes);
    scheduler.executeAlgorithm("FCFS");


    // FCFS::calculate(processes);
    // SJF::calculate(processes);

    return 0;
}