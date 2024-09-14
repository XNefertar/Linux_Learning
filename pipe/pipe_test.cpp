// #include <iostream>
// #include <cassert>
// #include <functional>
// #include <vector>
// #include <string>
// #include <unistd.h>
// #include <sys/types.h>
// #include <stdio.h>

// #define PROCESS_NUM 10
// #define TASK_NUM 3

// // 宏函数创建一个用于生成伪随机数的函数
// #define MakeSeed() srand((unsigned long)time(nullptr) ^ getpid() ^ 0x171237 ^ rand() % 1234)

// using func_ptr = void(*)();
// std::vector<func_ptr> func_task;

// class sub_end_ptr{
// public:
//     static int _num;
//     std::string _name;
//     pid_t _sub_id;
//     int _write_fd;

//     sub_end_ptr(pid_t sub_id, int write_fd)
//         :_sub_id(sub_id),
//         _write_fd(write_fd)
//     {
//         char name_buffer[64];
//         snprintf(name_buffer, sizeof name_buffer, "process-%d[pid(%d)-fd(%d)]", _num++, _sub_id, _write_fd);
//         _name = name_buffer;
//     }

// };


// void func1(){
//     std::cout << "Task : IO任务" << std::endl;
// }

// void func2(){
//     std::cout << "Task : CPU任务" << std::endl;
// }

// void func3(){
//     std::cout << "Task : 文件任务" << std::endl;
// }


// // 用于父进程写入待处理任务码
// int send_task(const sub_end_ptr& process, int task_num){
//     std::cout << "send task num " << task_num << " send to -> " << process._name << std::endl;
//     ssize_t s = write(process._write_fd, &task_num, sizeof task_num);
//     assert(s == sizeof(int));
//     (void)s; // 用于消除编译器的变量未使用的告警信息
//              // 没有其他用途
// }

// // 用于获取父进程提供的待处理任务码
// int recv_task(int read_fd){
//     int code = 0;
//     ssize_t s = read(read_fd, &code, sizeof code);

//     if(s == 4) return code;
//     else if(s <= 0) return -1;
//     else return 0;
// }


// void creat_sub_process(std::vector<sub_end_ptr>& subs, std::vector<func_ptr>& func_set){
//     std::vector<sub_end_ptr> sub_set;
//     for(int i = 0; i < PROCESS_NUM; ++i){  
//         int fds[2];
//         int n = pipe(fds);
//         assert(n == 0);

//         pid_t id = fork();
//         // 子进程处理
//         if(id == 0){

//             // 关闭写入数据端口
//             close(fds[1]);
//             while(1){
//                 // 处理任务
//                 int command_code = recv_task(fds[0]);
//                 if(command_code >= 0 && command_code < func_task.size()){
//                     func_task[command_code]();
//                 }
//                 else break;
//                 sleep(1);
//             }
//             // 直接退出
//             exit(0);
//         }
//         // 父进程处理
//         sub_end_ptr sub_tmp(id, fds[1]);
//         sub_set.push_back(sub_tmp);
        
//         // 关闭读入数据端口
//         close(fds[0]);
//     }
// }


// void load_balance_control(std::vector<sub_end_ptr>& sub_set){
//     for(int i = 0; i < 100; ++i) {
//         int sub_index = rand() % PROCESS_NUM;
//         int task_index = rand() % TASK_NUM;
//         send_task(sub_set[sub_index], task_index);
//     }

// }


// int sub_end_ptr::_num = 0;

// int main(){
//     MakeSeed();
//     // 模拟任务列表
//     func_task.push_back(func1);
//     func_task.push_back(func2);
//     func_task.push_back(func3);

//     std::vector<sub_end_ptr> sub_set;

//     creat_sub_process(sub_set, func_task);
//     load_balance_control(sub_set);
//     for(int i = 0; i < PROCESS_NUM; i++) close(sub_set[i]._write_fd); // waitpid();
//     return 0;
// }


#include <iostream>
#include <cassert>
#include <functional>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <ctime>

#define PROCESS_NUM 10
#define TASK_NUM 3

#define MakeSeed() srand((unsigned long)time(nullptr) ^ getpid() ^ 0x171237 ^ rand() % 1234)

using func_ptr = void(*)();
std::vector<func_ptr> func_task;

class sub_end_ptr{
public:
    static int _num;
    std::string _name;
    pid_t _sub_id;
    int _write_fd;

    sub_end_ptr(pid_t sub_id, int write_fd)
        :_sub_id(sub_id),
        _write_fd(write_fd)
    {
        char name_buffer[64];
        snprintf(name_buffer, sizeof name_buffer, "process-%d[pid(%d)-fd(%d)]", _num++, _sub_id, _write_fd);
        _name = name_buffer;
    }
};

// 模拟任务函数
void func1(){
    std::cout << "Task : IO任务" << std::endl;
}

void func2(){
    std::cout << "Task : CPU任务" << std::endl;
}

void func3(){
    std::cout << "Task : 文件任务" << std::endl;
}

// 父进程写入待处理任务码
int send_task(const sub_end_ptr& process, int task_num){
    std::cout << "父进程: 发送任务 " << task_num << " 给 -> " << process._name << std::endl;
    ssize_t s = write(process._write_fd, &task_num, sizeof task_num);
    assert(s == sizeof(int));
    (void)s;
    return 0;
}

// 子进程读取任务码
int recv_task(int read_fd){
    int code = 0;
    ssize_t s = read(read_fd, &code, sizeof code);
    if(s == sizeof(int)) return code;
    else if(s <= 0) return -1;
    else return 0;
}

// 创建子进程并进行管道通信
void creat_sub_process(std::vector<sub_end_ptr>& sub_set, std::vector<func_ptr>& func_set){
    for(int i = 0; i < PROCESS_NUM; ++i){  
        int fds[2];
        int n = pipe(fds);
        assert(n == 0);

        pid_t id = fork();
        if(id == 0){
            // 子进程处理
            close(fds[1]); // 关闭写端
            while(1){
                int command_code = recv_task(fds[0]);
                if(command_code >= 0 && command_code < func_task.size()){
                    // 打印子进程接收任务信息
                    std::cout << "子进程[pid: " << getpid() << "]: 处理任务 " << command_code << std::endl;
                    func_task[command_code]();
                }
                else break; // 如果收到无效任务码，退出
                sleep(1);  // 模拟任务处理延迟
            }
            close(fds[0]); // 关闭读端
            exit(0);
        }
        sub_end_ptr sub_tmp(id, fds[1]);
        sub_set.push_back(sub_tmp);
        close(fds[0]); // 父进程关闭读端
    }
}

// 负载均衡控制，将任务分配给子进程
void load_balance_control(std::vector<sub_end_ptr>& sub_set){
    for(int i = 0; i < 10; ++i) {  // 将无限循环改为一个有限循环便于观察
        int sub_index = rand() % PROCESS_NUM;
        int task_index = rand() % TASK_NUM;
        send_task(sub_set[sub_index], task_index); // 发送任务给子进程
        sleep(1);  // 增加间隔，便于观察
    }
}

int sub_end_ptr::_num = 0;

int main(){
    MakeSeed();  // 初始化随机数种子

    // 模拟任务列表
    func_task.push_back(func1);
    func_task.push_back(func2);
    func_task.push_back(func3);

    std::vector<sub_end_ptr> sub_set;

    creat_sub_process(sub_set, func_task);  // 创建子进程
    load_balance_control(sub_set);          // 向子进程分配任务

    // 父进程关闭所有写端口
    for(int i = 0; i < PROCESS_NUM; i++) {
        close(sub_set[i]._write_fd);
    }

    // 等待所有子进程退出
    for(int i = 0; i < PROCESS_NUM; i++) {
        waitpid(sub_set[i]._sub_id, nullptr, 0);
    }

    return 0;
}
