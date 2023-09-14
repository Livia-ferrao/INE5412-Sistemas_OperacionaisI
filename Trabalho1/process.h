#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include "context.h"
using namespace std;

class Process {
public:
    Process(int c, int d, int p, int pid);
    ~Process();


    friend std::ostream &operator<<(std::ostream& os, const Process& p);
    void print_process_context();

    int get_id() const;
    void set_id(int _id);
    int get_creation_time() const;
    void set_creation_time(int _creation_time);
    int get_duration() const;
    void set_duration(int _duration);
    int get_priority() const;
    void set_priority(int _priority);
    int get_waiting_time() const;
    void set_waiting_time(int _waiting_time);
    int get_turnround_time() const;
    void set_turnround_time(int _turnround_time);
    int get_remaining_time() const;
    void set_remaining_time(int _remaining_time);
    int get_begin() const;
    void set_begin(int _begin);
    int get_end() const;
    void set_end(int _end);
    std::string get_state() const;
    void set_state(const std::string& _state);
    Context* get_p_context();
    void set_p_context(const Context& _p_context);

private:
    int id;
    int creation_time;
    int duration;
    int priority;
    int waiting_time;
    int turnround_time;
    int remaining_time;
    int begin;
    int end;
    std::string state;
    Context p_context;
};

#endif
