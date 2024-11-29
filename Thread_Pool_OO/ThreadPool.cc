#include "ThreadPool.hpp"
ThreadPool::ThreadPool(size_t threadNum, size_t queueSize)
    : _threadNum(threadNum),
      _queueSize(queueSize),
      _taskQueue(_queueSize),
      _isExit(false)
{
    _threadSet.reserve(_threadNum);
}

void ThreadPool::thread_pool_start(){
    // 创建工作线程
    for(int i = 0; i < _threadNum; ++i){
        _threadSet.push_back(std::unique_ptr<Thread>(new WorkThread1(*this)));
    }
    // 运行工作线程
    for(auto& it : _threadSet){
        it->thread_start();
    }
}

void ThreadPool::thread_pool_stop()
{
    for (auto &it : _threadSet){
        it->thread_join();
    }
    _isExit = true;
}

void ThreadPool::add_task(Task *param){
    _taskQueue.push_task(param);
}

Task* ThreadPool::get_task(){
    Task* task = _taskQueue.pop_task();
    if (task == nullptr) {
        std::cout << "get_task() returned nullptr" << std::endl;
    }
    return task;
}

void ThreadPool::exec_task(){
    while (!_isExit){
        Task *task = get_task();
        if (task != nullptr)
        {
            // std::cout << std::boolalpha << (typeid(*task) == typeid(MyTask)) << std::endl;
            // std::cout << std::noboolalpha;
            task->process();
        }
        else
        {
            std::cout << "NULL TASK" << std::endl;
        }
    }
}