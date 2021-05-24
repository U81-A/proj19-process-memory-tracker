#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
// #include "process.h"

using namespace std;

void show(vector<process> list);
vector<process> process_sort(vector<process> list, string target, bool direction);
vector<process> process_top(vector<process> list, int num);
vector<process> process_specific(vector<process> list, int pid);

bool com_pid_pos(const process &p1, const process &p2){
    return p1.pid > p2.pid;
}

bool com_pid_neg(const process &p1, const process &p2){
    return p1.pid < p2.pid;
}

bool com_mem_pos(const process &p1, const process &p2){
    return p1.memory > p2.memory;
}

bool com_mem_neg(const process &p1, const process &p2){
    return p1.memory < p2.memory;
}

vector<process> process_sort(vector<process> list, string target, bool direction){
    if (target=="pid"){
        if (direction){
            sort(list.begin(), list.end(), com_pid_pos);
        }else{
            sort(list.begin(), list.end(), com_pid_neg);
        }
    }
    else if (target=="memory"){
        if (direction){
            sort(list.begin(), list.end(), com_mem_pos);
        }else{
            sort(list.begin(), list.end(), com_mem_neg);
        }
    }
    return list;
}

vector<process> process_top(vector<process> list, int num){
    int count = 0;
    for (vector<process>::iterator it = list.begin(); it!=list.end();){
        count++;
        if (count > num)
        {
            /* code */
            it = list.erase(it);
        }
        else
        {
            it++;
        }
    }
    return list;
}

vector<process> process_specific(vector<process> list, int pid){
    int count = 0;
    for (vector<process>::iterator it = list.begin(); it!=list.end();){
        if (list[count].pid!=pid)
        {
            /* code */
            it = list.erase(it);
        }
        else
        {
            it++;
        }
        count++;
    }
    return list;
}
