#ifndef __TASK_QUEUE_HPP__
#define __TASK_QUEUE_HPP__

#include <iostream>
#include <queue>
#include "Condition.hpp"
#include "MutexLockGuard.hpp"

class TaskQueue
{
private:
    std::queue<int> _TaskQueue;
    int _QueueSize;
    Condition _notFull;  // 生产者
    Condition _notEmpty; // 消费者
    MutexLock _mutex;

public:
    TaskQueue(int size)
    : _QueueSize(size),
      _notFull(_mutex),
      _notEmpty(_mutex)
    {}

    ~TaskQueue() = default;

    void push(const int& data){
        {
            MutexLockGuard lk(_mutex);
            // 为什么采用轮询？
            // 因为 POSIX 标准下会出现虚假唤醒
            // 主要是 pthread_cond_signal 会唤醒一个或多个条件变量
            while(Full()){
                _notFull.Wait();
            }
            _TaskQueue.push(data);
            std::cout << ">> Producer put number " << data << " in TaskQueue." << std::endl;
            _notEmpty.notifySignal();
        }
    }

    int pop(){
        int ret = 0;
        {
            MutexLockGuard lk(_mutex);
            while(Empty()){
                _notEmpty.Wait();
            }
            ret = _TaskQueue.front();
            _TaskQueue.pop();
            std::cout << "<< Consumer pop data " << ret << " in TaskQueue." << std::endl;
            _notFull.notifySignal();
        }
        return ret;
    }

    bool Empty(){
        return _TaskQueue.empty();
    }

    bool Full(){
        return _QueueSize == _TaskQueue.size();
    }

};



#endif // __TASK_QUEUE_HPP__