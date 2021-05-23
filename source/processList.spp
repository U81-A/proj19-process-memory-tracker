#include <iostream>
#include <vector>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <dirent.h>
#include <fstream>


using namespace std;

struct process {
    /* data */
    int pid;
    int memory;
};

void listFiles(const char * dir);
void scanDirectorFromPath(const char* path);
bool isNum(string str);
vector<process> fetchProcessList();
string _commend;
vector <string> dirs;
vector <string> process_dirs;
vector <process> process_list;

#include <sstream>

//int main() {

vector<process> fetchProcessList(){


//    _commend = "cat /proc";
//    system("cat /proc");

//    char tar_dir[] = "D:\\Clion_projects\\";
    char tar_dir[] = "/proc/";

//    strcat(tar_dir, "*.*");
//    listFiles(tar_dir);
    scanDirectorFromPath(tar_dir);
    cout << "--------- dirs ---------" << endl;
//    for (auto a : dirs) cout << a << endl;
    for (int i = 0;i<dirs.size();++i){
        cout << dirs[i] << endl;
        if (isNum(dirs[i])) {
//            cout << "This is a folder for process " << dirs[i] << endl;
            process_dirs.push_back(dirs[i]);
        }else {
//            cout << "This is not a process " << endl;
        }
    }

    ifstream infile;

    for (int i = 0;i<process_dirs.size();i++){

        string pid = process_dirs[i];
        infile.open(("/proc/"+pid+"/statm").c_str(), ios::in);

        if(!infile.is_open ())
            cout << "Open file failure" << endl;

        string temp;
        while(getline(infile,temp)){
            istringstream str(temp);
            string data;
            vector<string> datas;
            while (str >> data) {
                datas.push_back(data);
            }
            cout << "Process " << pid << " memory is " << datas[1] << "*4 KB" << endl;
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

    for (int i = 0;i<process_list.size();++i) {
        cout << process_list[i].pid << " " << process_list[i].memory << endl;
    }

//    _commend = "cat /proc/PID/status";
//    system("cat /proc/PID/status");

    return process_list;
}



void listFiles(const char * dir)
{
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

void scanDirectorFromPath(const char* path)
{
    DIR *dir;
    dir = opendir(path);
    if(dir == NULL){
        cout<<"Open Dir failed!"<<endl;
        return;
    }
    struct dirent *dirent_;
    while(dirent_ = readdir(dir))
    {
        string dir_name = dirent_ ->d_name;
        //ignore . or .. file
        if(dir_name  == "." || dir_name  == ".."){
            continue;
        }else if (dir_name .find(".cms") != string::npos){
            size_t start_pos = dir_name.find_first_of("_");
            int appID = atoi(dir_name.substr(0,start_pos ).c_str());
            size_t end_pos = dir_name.find_last_of("_");
            int orgID = atoi(dir_name.substr(start_pos +1,end_pos ).c_str());
            cout<< "CMS File's appID:"<<appID <<endl;
            cout<< "CMS File's orgID:"<<orgID <<endl;
        }
        cout<< " File's Name:"<<dir_name <<endl;
        dirs.push_back(dir_name);


    }
}

bool isNum(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        int tmp = (int)str[i];
        if (tmp >= 48 && tmp <= 57)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
