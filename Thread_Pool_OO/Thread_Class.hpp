#ifndef __THREAD_HPP__
#define __THREAD_HPP__
#include <queue>
#include <functional>
#include <pthread.h>
#include <unistd.h>
#include "TaskQueue.hpp"
#include "ThreadPool.hpp"

class ThreadPool;

class Thread
{
private:
    pthread_t _thID;
    bool _isRunning;

public:
    Thread();

    static void* ThreadFunc(void* args);

    void thread_start();
    void thread_join();

    virtual void run() = 0;
};

class WorkThread1
:public Thread
{
private:
    ThreadPool& _pool;
public:
    WorkThread1(ThreadPool& pool);
    ~WorkThread1() = default;

    virtual void run() override;
};

#endif // __THREAD_HPP__