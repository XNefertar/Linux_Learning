#ifndef __THREAD_PC_HPP__
#define __THREAD_PC_HPP__
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "TaskQueue.hpp"

class Thread
{
public:
    virtual void run() = 0;
    virtual void start() = 0;
    // virtual void stop() = 0;
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
        std::srand(std::time(nullptr) ^ getpid());
        int random_number = std::rand();
        _taskQueue.push(random_number);
        std::cout << ">> Producer put number " << random_number << " in TaskQueue." << std::endl; 
    }

    virtual void start() override{
        while(true){
            this->run();
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
        int ret = _taskQueue.pop();
        std::cout << "<< Consumer pop data " << ret << " in TaskQueue." << std::endl;
    }

    virtual void start() override{
        while(true){
            this->run();
            sleep(1);
        }
    }

};

#endif // __THREAD_PC_HPP__