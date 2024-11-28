#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

#include <vector>
#include <memory>
#include <iostream>
#include "Task.hpp"
#include "TaskQueue.hpp"
#include "Thread_Class.hpp"
class Thread;
class ThreadPool
{
    friend class WorkThread1;
private:
    size_t _threadNum;
    size_t _queueSize;
    std::vector<std::unique_ptr<Thread>> _threadSet;
    TaskQueue _taskQueue;
    bool _isExit;

public:
    ThreadPool(size_t threadNum, size_t queueSize);
    ~ThreadPool() = default;

    void thread_pool_start();
    void thread_pool_stop();
    
    void add_task(Task* param);

private:
    Task* get_task();
    void exec_task();
};


#endif // __THREAD_POOL_HPP__