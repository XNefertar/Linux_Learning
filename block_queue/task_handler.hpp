#ifndef _TASK_HANDLER_HPP
#define _TASK_HANDLER_HPP

#include <iostream>
#include <string>
#include <functional>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

using func_ptr = std::function<double (int, int, char)>;

class Cal_Task{
private:
    int _a;
    int _b;
    char _operator_signal;
    func_ptr _fptr;
public:
    // 构造函数
    Cal_Task() = default;
    Cal_Task(int a, int b, char operator_signal, func_ptr fptr)
        :_a(a),
        _b(b),
        _operator_signal(operator_signal),
        _fptr(fptr)
    {}

    std::string operator()(){
        int result = _fptr(_a, _b, _operator_signal);
        char buffer[1024]{};
        snprintf(buffer, sizeof buffer, "%d %c %d = %d", _a, _operator_signal, _b, result);
        return buffer;
    }
    std::string to_string(){
        char buffer[1024]{};
        snprintf(buffer, sizeof buffer, "%d %c %d = ?", _a, _operator_signal, _b);
        return buffer;
    }
};


using func_t = std::function<void(const std::string&)>;

class Save_Task{
private:
    std::string _messege;
    func_t _func_ptr;

public:

    Save_Task(std::string messege = "", func_t fp = nullptr)
        :_messege(messege),
        _func_ptr(fp)
    {}

    void operator()(){
        _func_ptr(_messege);
    }
};


int mymath(int a, int b, char operator_signal){
    switch(operator_signal){
        case '+':{
            // 加法
            return a + b;
            break;
        }
        case '-':{
            // 减法
            return a - b;
            break;
        }
        case '*':{
            // 乘法
            return a * b;
            break;
        }
        case '/':{
            // 除法
            if(b == 0){
                std::cerr << "wrong argument... " ;
                return -1;
            }
            return a / b;
            break;
        }
        default:{
            // return nullptr;
            break;
        }
    }
}

void _save(const std::string &str){
    umask(0);
    int fd = open("./log.txt", O_CREAT | O_RDWR | O_APPEND, 0666);
    ssize_t s = write(fd, str.c_str(), str.size());
    close(fd);
}

// int _add(int a, int b){
//     return a + b;    
// }

// int _sub(int a, int b){
//     return a - b;    
// }

// int _mul(int a, int b){
//     return a * b;    
// }

// int _div(int a, int b){
//     if(b == 0){
//         std::cout << "error argument... ";
//         return -1; 
//     }
//     return a / b;    
// }


// func_ptr get_func_ptr(int operator_code){
//     switch(operator_code){
//         case 0:{
//             // 加法
//             return _add;
//             break;
//         }
//         case 1:{
//             // 减法
//             return _sub;
//             break;
//         }
//         case 2:{
//             // 乘法
//             return _mul;
//             break;
//         }
//         case 3:{
//             // 除法
//             return _div;
//             break;
//         }
//         default:{
//             return nullptr;
//             break;
//         }
//     }
// }




#endif