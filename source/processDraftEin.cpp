//
// Created by XI Ruiling on 2021/5/24.
//

#include <iostream>
#include <vector>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include <string>
#include <algorithm>

const wchar_t TAB_THIN_VERTICAL = L'\u2502';

using namespace std;

struct process {
    /* data */
    int pid;
    int memory;
};

void listFiles(const char *dir);

void scanDirectorFromPath(const char *path);

bool isNum(string str);

void user_call();

vector<process> process_sort(vector<process> list, string target, bool direction);

vector<process> process_top(vector<process> list, int num);

vector<process> process_specific(vector<process> list, int pid);

vector<process> fetchProcessList();

string _commend;
vector<string> dirs;
vector<string> process_dirs;
vector<process> process_list;

#include <sstream>

bool com_pid_pos(const process &p1, const process &p2) {
    return p1.pid > p2.pid;
}

bool com_pid_neg(const process &p1, const process &p2) {
    return p1.pid < p2.pid;
}

bool com_mem_pos(const process &p1, const process &p2) {
    return p1.memory > p2.memory;
}

bool com_mem_neg(const process &p1, const process &p2) {
    return p1.memory < p2.memory;
}

vector<process> process_sort(vector<process> list, string target, bool direction) {
    if (target == "pid") {
        if (direction) {
            sort(list.begin(), list.end(), com_pid_pos);
        } else {
            sort(list.begin(), list.end(), com_pid_neg);
        }
    } else if (target == "memory") {
        if (direction) {
            sort(list.begin(), list.end(), com_mem_pos);
        } else {
            sort(list.begin(), list.end(), com_mem_neg);
        }
    }
    return list;
}

vector<process> process_top(vector<process> list, int num) {
    int count = 0;
    for (vector<process>::iterator it = list.begin(); it != list.end();) {
        count++;
        if (count > num) {
            /* code */
            it = list.erase(it);
        } else {
            it++;
        }
    }
    return list;
}

vector<process> process_specific(vector<process> list, int pid) {
    int count = 0;
    for (vector<process>::iterator it = list.begin(); it != list.end();) {
        if (list[count].pid != pid) {
            /* code */
            it = list.erase(it);
        } else {
            it++;
        }
        count++;
    }
    return list;
}

vector<process> fetchProcessList() {


//    _commend = "cat /proc";
//    system("cat /proc");

//    char tar_dir[] = "D:\\Clion_projects\\";
    char tar_dir[] = "/proc/";

//    strcat(tar_dir, "*.*");
//    listFiles(tar_dir);
    scanDirectorFromPath(tar_dir);
    // cout << "--------- dirs ---------" << endl;
//    for (auto a : dirs) cout << a << endl;
    for (int i = 0; i < dirs.size(); ++i) {
        // cout << dirs[i] << endl;
        if (isNum(dirs[i])) {
//            cout << "This is a folder for process " << dirs[i] << endl;
            process_dirs.push_back(dirs[i]);
        } else {
//            cout << "This is not a process " << endl;
        }
    }

    ifstream infile;

    for (int i = 0; i < process_dirs.size(); i++) {

        string pid = process_dirs[i];
        infile.open(("/proc/" + pid + "/statm").c_str(), ios::in);

        if (!infile.is_open())
            cout << "Open file failure" << endl;

        string temp;
        while (getline(infile, temp)) {
            istringstream str(temp);
            string data;
            vector<string> datas;
            while (str >> data) {
                datas.push_back(data);
            }
            // cout << "Process " << pid << " memory is " << datas[1] << "*4 KB" << endl;
            int i_pid, i_mem;
            istringstream new_pid(pid);
            new_pid >> i_pid;
            istringstream new_mem(datas[1]);
            new_mem >> i_mem;
            process_list.push_back(process{i_pid, i_mem});
        }
//
//        while (!infile.eof())            // 若未到文件结束一直循环
//        {
//
//        }
        infile.close();
//        break;


    }
    // ofstream proc_output;
    // proc_output.open("usualMode.txt", ofstream::trunc);
    // if (proc_output.is_open()) {
    //     for (int i = 0;i<process_list.size();++i) {
    //         setlocale(LC_ALL,"en_US.UTF-8");
    //         // cout<<setw(10)<<process_list[i].pid<<setw(10)<<process_list[i].memory<<endl;
    //         cout<<setw(10)<<process_list[i].pid<<setw(10)<<process_list[i].memory<<endl;
    //     }
    //     proc_output.close();
    // } else cout << "Unable to open the file";



//    _commend = "cat /proc/PID/status";
//    system("cat /proc/PID/status");

    return process_list;
}


void listFiles(const char *dir) {
    /*intptr_t handle;
    _finddata_t findData;
    handle = _findfirst(dir, &findData);    // 查找目录中的第一个文件
    if (handle == -1)
    {
        cout << "Failed to find first file!\n";
        return;
    }
    do
    {
        if (findData.attrib & _A_SUBDIR
            && strcmp(findData.name, ".") != 0
            && strcmp(findData.name, "..") != 0
                )    // 是否是子目录并且不为"."或".."
        {
//            cout << findData.name << " is dir" << endl;
            dirs.emplace_back(findData.name);
        }
        else{
//            cout << findData.attrib << " "  ;
//            cout << findData.name << "\t" << " is file" << endl;
        }
    } while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件
    cout << "Done!\n";
    _findclose(handle);    // 关闭搜索句柄*/
}

void scanDirectorFromPath(const char *path) {
    DIR *dir;
    dir = opendir(path);
    if (dir == NULL) {
        cout << "Open Dir failed!" << endl;
        return;
    }
    struct dirent *dirent_;
    while (dirent_ = readdir(dir)) {
        string dir_name = dirent_->d_name;
        //ignore . or .. file
        if (dir_name == "." || dir_name == "..") {
            continue;
        } else if (dir_name.find(".cms") != string::npos) {
            size_t start_pos = dir_name.find_first_of("_");
            int appID = atoi(dir_name.substr(0, start_pos).c_str());
            size_t end_pos = dir_name.find_last_of("_");
            int orgID = atoi(dir_name.substr(start_pos + 1, end_pos).c_str());
            // cout<< "CMS File's appID:"<<appID <<endl;
            // cout<< "CMS File's orgID:"<<orgID <<endl;
        }
        // cout<< " File's Name:"<<dir_name <<endl;
        dirs.push_back(dir_name);


    }
}

bool isNum(string str) {
    for (int i = 0; i < str.size(); i++) {
        int tmp = (int) str[i];
        if (tmp >= 48 && tmp <= 57) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}


int main() {
    vector<process> origin_proc_list = fetchProcessList();
    user_call();
    cout << "end with failure" << endl;
}

void user_call() {
    while (true) {
        char mode;
        cout << "Input [a] or [b] or [c]:\n[a]:\tspecific\n[b]:\tsorted\n[c]:\tfind the top N memory cosumed PID\n"
             << endl;
        cin >> mode;
        vector<process> origin;
        vector<process> result;
        if (mode == 'a') {
            int pid;
            cout << "Enter specific mode. Pls input the PID: " << endl;
            cin >> pid;
            while (true) {
                origin = fetchProcessList();
                result = process_specific(origin, pid);
                system("CLS");
                for (int i = 0; i < result.size(); ++i) {
                    cout << setw(10) << process_list[i].pid << setw(10) << process_list[i].memory << endl;
                }
                usleep(1000000);
            }
            break;
        } else if (mode == 'b') {
            /* code */
            char order;
            cout
                    << "Enter sorted mode. Pls select the order:\n[a]:\t Ascend PID\n[b]:\tDescend PID\n[c]:\tAscend memory consuming\n[d]:\tDescend memory consuming"
                    << endl;
            cin >> order;
            while (true) {
                /* code */
                if (order == 'a') {
                    while (true) {
                        origin = fetchProcessList();
                        result = process_sort(origin, "pid", true);
                        system("CLS");
                        for (int i = 0; i < result.size(); ++i) {
                            cout << setw(10) << process_list[i].pid << setw(10) << process_list[i].memory << endl;
                        }
                        usleep(1000000);
                    }
                    break;
                } else if (order == 'b') {
                    /* code */
                    while (true) {
                        origin = fetchProcessList();
                        result = process_sort(origin, "pid", false);
                        system("CLS");
                        for (int i = 0; i < result.size(); ++i) {
                            cout << setw(10) << process_list[i].pid << setw(10) << process_list[i].memory << endl;
                        }
                        usleep(1000000);
                    }
                    break;
                } else if (order == 'c') {
                    /* code */
                    while (true) {
                        origin = fetchProcessList();
                        result = process_sort(origin, "memory", true);
                        system("CLS");
                        for (int i = 0; i < result.size(); ++i) {
                            cout << setw(10) << process_list[i].pid << setw(10) << process_list[i].memory << endl;
                        }
                        usleep(1000000);
                    }
                    break;
                } else if (order == 'd') {
                    /* code */
                    while (true) {
                        origin = fetchProcessList();
                        result = process_sort(origin, "memory", false);
                        system("CLS");
                        for (int i = 0; i < result.size(); ++i) {
                            cout << setw(10) << process_list[i].pid << setw(10) << process_list[i].memory << endl;
                        }
                        usleep(1000000);
                    }
                    break;
                } else {
                    cout << "Wrong input. Pls input again.";
                }
            }
            break;
        } else if (mode == 'c') {
            /* code */
            int num;
            cout << "Provide top N memory consuming thread. Input N:" << endl;
            cin >> num;
            while (true) {
                origin = fetchProcessList();
                result = process_top(origin, num);
                system("CLS");
                for (int i = 0; i < result.size(); ++i) {
                    cout << setw(10) << process_list[i].pid << setw(10) << process_list[i].memory << endl;
                }
                usleep(1000000);
            }
            break;
        } else {
            cout << "Wrong input. Pls input again.";
        }
    }
}
