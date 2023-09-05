#ifndef SJF_H
#define SJF_H

#include<vector>
#include "Process.cc"

class SJF {
    public:
        struct CompareProcessesDuration {
            bool operator()(const Process* a, const Process* b) const {
                return a->duration > b->duration;
            }
        };

        static void calculate(std::vector<Process*> processes);
};

#endif
