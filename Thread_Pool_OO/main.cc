#include <iostream>
#include <memory>
#include "TaskQueue.hpp"
#include "ThreadPool.hpp"
#include "Task.hpp"
#include "Thread_Class.hpp"

int main()
{
    ThreadPool tp(4, 10);
    for(int i = 0; i < 15; ++i){
        tp.add_task(std::unique_ptr<Task>(new MyTask()).get());
    }
    tp.thread_pool_start();
    tp.thread_pool_stop();

    return 0;
}