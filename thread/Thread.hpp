#ifndef _THREAD_HPP
#define _THREAD_HPP

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <cassert>
#include <unistd.h>

using func_ptr = void*(*)(void*);

class Thread;


// 线程封装

class Thread{

    friend void* start_routine(void*);

private:
    int        _number;
    pthread_t  _tid;
    func_ptr   _start_routine;
    void*      _args;
    char       _buffer[1024];
public:

    // 构造函数
    Thread(int num = 0, func_ptr start_routine = nullptr, void* args = nullptr)
        :_number(num),
        _start_routine(start_routine),
        _args(args)
    {
        snprintf(_buffer, sizeof(_buffer), "%d : 0x%x", _number, _tid);
        int n = pthread_create(&_tid, nullptr, _start_routine, this->_args);
        assert(0 == n);
        (void)n;
    }


    // 类外全局函数不可访问类内的私有成员变量
    // 类内成员方法的形参具有隐藏的this指针
    // 所以必须使用static声明
    // 但是static函数属于静态方法
    // 不可调用成员变量或方法

    // 解决方法：
    // 1：友元函数——通过在类外声明的友元函数（全局函数），可以访问类内的私有成员变量
    // 2: C++11启用的thread_local关键字，可以使一个静态成员变量在多线程内做到独立拥有一个实例化对象
    // 3: 通过创建另一个类，然后通过该类进行间接调用成员方法或变量

    // 这里采用友元函数的方法，因为它较为简单，且代码实现较容易理解
    // static void* start_routine(void* args){
    //     Thread* func_var = static_cast<Thread*>(args);
        
    // }

    // 默认析构函数
    ~Thread() = default;


    // 线程合并
    void join(){
        int n = pthread_join(_tid, nullptr);
        std::cout << this->_buffer << " is joining..." << std::endl;
        assert(0 == n);
        (void)n;
    }
};

void* start_routine(void* args){
    Thread* td = static_cast<Thread*>(args);
    void* ret = td->_start_routine(td->_args);
    return ret;
}


#endif