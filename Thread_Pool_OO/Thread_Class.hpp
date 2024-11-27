#include <queue>
#include <functional>
#include <pthread.h>
#include <unistd.h>
#include "TaskQueue.hpp"
#ifndef __THREAD_HPP__
#define __THREAD_HPP__

class Thread
{
protected:

    pthread_t _thID;
    bool _isRunning;

public:
    Thread()
        : _thID(0),
          _isRunning(false)
    {}

    static void* ThreadFunc(void* args){
        Thread* temp = static_cast<Thread*>(args);
        if(temp){
            temp->run();
        }
        return nullptr;
    }

    void thread_start(){
        pthread_create(&_thID, nullptr, ThreadFunc, this);
    }
    void thread_join(){
        pthread_join(_thID, nullptr);
    }

    virtual void run() = 0;
};

class WorkThread1
    : public Thread
{
private:
    TaskQueue& _taskQueue;
public:
    WorkThread1(TaskQueue& taksQueue)
        : _taskQueue(taksQueue)
    {}
    virtual void run() override {
        while(true){
            Task* task = _taskQueue.get_task();
            if(task){
                task->set_result(task->get_param1() + task->get_param2());
                std::cout << "param1[" << task->get_param1() << "]" << " + " <<\
                 "param2[" << task->get_param2() << "]" << \
                 " result # " << task->get_result() << std::endl;
                _taskQueue.pop_task();
            }
            else break;
            sleep(1);
        }
    }
};

#endif // __THREAD_HPP__