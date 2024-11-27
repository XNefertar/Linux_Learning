#ifndef __THREAD_PC_HPP__
#define __THREAD_PC_HPP__
#include <iostream>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "TaskQueue.hpp"

class Thread
{
private:
    bool _isRunning;
    pthread_t _ThreadID;
public:
    virtual void run() = 0;
    Thread()
    : _ThreadID(0),
      _isRunning(false)
    {}

    static void* ThreadFunc(void* args){
        Thread* pth = static_cast<Thread*>(args);
        if(pth)
            pth->run();
        else
            std::cerr << "ERROR STATIC CAST" << std::endl;

        return nullptr;
    }

    void ThreadStart(){
        int ret = pthread_create(&_ThreadID, nullptr, ThreadFunc, this);
        if(ret < 0){
            std::cerr << "ERROR PTHREAD CREATE." << std::endl;
        }
        _isRunning = true;
    }

    void ThreadStop(){
        if(_isRunning){
            pthread_join(_ThreadID, nullptr);
        }
        _isRunning = false;
    }
};

class Producer
:public Thread
{
private:
    TaskQueue& _taskQueue;

public:
    Producer(TaskQueue& taskQueue)
    : _taskQueue(taskQueue)
    {}

    virtual void run() override{
        for(;;){
            std::srand(std::time(nullptr) ^ getpid());
            int random_number = std::rand();
            _taskQueue.push(random_number);
            sleep(1);
        }
    }
};

class Consumer
:public Thread
{
private:
    TaskQueue& _taskQueue;
public:
    Consumer(TaskQueue& taskQueue)
    : _taskQueue(taskQueue)
    {}

    virtual void run() override{
        for(;;){
            int ret = _taskQueue.pop();
            sleep(1);
        }
    }
};

#endif // __THREAD_PC_HPP__