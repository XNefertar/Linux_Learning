#include <iostream>
#include <memory>
#include "TaskQueue.hpp"
#include "ThreadPool.hpp"
#include "Task.hpp"
#include "Thread_Class.hpp"

int main()
{
    TaskQueue _taskQueue(10);
    int rand = 10;

    for(int i = 0; i < 10; ++i){
        _taskQueue.push_task(rand - i, rand % (i + 1));
    }

    std::unique_ptr<Thread> Thread1(new WorkThread1(_taskQueue));


    Thread1->thread_start();
    Thread1->thread_join();
}