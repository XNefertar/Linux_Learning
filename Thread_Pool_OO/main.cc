#include <iostream>
#include <memory>
#include "TaskQueue.hpp"
#include "ThreadPool.hpp"
#include "Task.hpp"
#include "Thread_Class.hpp"

int main()
{
    ThreadPool tp(4, 10);
    for(int i = 0; i < 10; ++i){
        std::unique_ptr<Task> temp(new MyTask());
        tp.add_task(std::move(temp.get()));
    }
    tp.thread_pool_start();
    tp.thread_pool_stop();

    return 0;
}