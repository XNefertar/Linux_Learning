#ifndef _TASK_HANDLER_HPP
#define _TASK_HANDLER_HPP

#include <iostream>
#include <string>
#include <functional>
#include <stdio.h>
#include <unistd.h>


using func_ptr = std::function<double (int, int, char)>;

class Task{
private:
    int _a;
    int _b;
    char _operator_signal;
    func_ptr _fptr;
public:
    // 构造函数
    Task() = default;
    Task(int a, int b, char operator_signal, func_ptr fptr)
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


#endif