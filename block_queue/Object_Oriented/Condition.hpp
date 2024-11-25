#ifndef __CONDITION_HPP__
#define __CONDITION_HPP__

#include "MutexLock.hpp"

class Condition
{
private:
    MutexLock& _mutexLock;
    pthread_cond_t _cond;
public:
    Condition(MutexLock& mutexLock)
    :_mutexLock(mutexLock)
    {
        pthread_cond_init(&_cond, nullptr);
    }
    ~Condition()
    {
        pthread_cond_destroy(&_cond);
    }

    // 单条件变量唤醒
    // 但是 POSIX 中说明可能会唤醒一个或多个条件变量
    // 所以之后的检查操作需要改为轮询机制
    void notifySignal(){
        pthread_cond_signal(&_cond);
    }
    // broadcast
    // 广播式唤醒所有条件变量
    void notifyAll(){
        pthread_cond_broadcast(&_cond);
    }

    void Wait(){
        pthread_cond_wait(&_cond, _mutexLock.GetMutexPtr());
    }

};


#endif // __CONDITION_HPP__