#include <queue>
#include <pthread.h>
#include "Task.hpp"

#ifndef __MUTEX_LOCK_GUARD_HPP__
#define __MUTEX_LOCK_GUARD_HPP__

class MutexLock {
private:
    pthread_mutex_t _mutex;

public:
    MutexLock(){
        pthread_mutex_init(&_mutex, nullptr);
    }

    MutexLock(pthread_mutex_t &mutex)
        :_mutex(mutex)
    {
        pthread_mutex_init(&_mutex, nullptr);
    }

    ~MutexLock() {
        pthread_mutex_destroy(&_mutex);
    }

    void lock() {
        pthread_mutex_lock(&_mutex);
    }

    void unlock() {
        pthread_mutex_unlock(&_mutex);
    }

    pthread_mutex_t* get_native_mutex() {
        return &_mutex;
    }

    // 禁用复制和赋值（互斥锁不可复制）
    MutexLock(const MutexLock&) = delete;
    MutexLock& operator=(const MutexLock&) = delete;
};

class MutexLockGuard {
private:
    MutexLock& _mutex_lock;

public:
    explicit MutexLockGuard(MutexLock& mutex_lock)
        : _mutex_lock(mutex_lock) {
        _mutex_lock.lock();  // 构造时加锁
    }

    ~MutexLockGuard() {
        _mutex_lock.unlock();  // 析构时解锁
    }

    // 禁用复制和赋值（锁守卫不可复制）
    MutexLockGuard(const MutexLockGuard&) = delete;
    MutexLockGuard& operator=(const MutexLockGuard&) = delete;
};
#endif // __MUTEX_LOCK_GUARD_HPP__




#ifndef __CONDITION_HPP__
#define __CONDITION_HPP__

class Condition
{
private:
    pthread_cond_t _cond;
    MutexLock &_mutexLock;

public:
    Condition(MutexLock &mutexLock)
        :_mutexLock(mutexLock)
    {
        pthread_cond_init(&_cond, nullptr);
    }

    ~Condition(){
        pthread_cond_destroy(&_cond);
    }

    int cond_wait(){
        return pthread_cond_wait(&_cond, _mutexLock.get_native_mutex());
    }

    int cond_singal(){
        return pthread_cond_signal(&_cond);
    }

    int cond_broadcast(){
        return pthread_cond_broadcast(&_cond);
    }
};
#endif // __CONDITION_HPP__



#ifndef __TASK_QUEUE_HPP__
#define __TASK_QUEUE_HPP__

class TaskQueue
{
private:
    int _queueSize;
    std::queue<Task*> _tasksQueue;
    MutexLock _mutexLock;
    Condition _notEmpty;
    Condition _notFull;
public:
    bool Empty(){
        return _tasksQueue.empty();
    }
    bool Full(){
        return _tasksQueue.size() == _queueSize;
    }

    TaskQueue(int size)
        : _queueSize(size),
          _notEmpty(_mutexLock),
          _notFull(_mutexLock)
    {}

    void push_task(Task* param){
        {
            MutexLockGuard lk(_mutexLock);
            while(Full()){
                _notFull.cond_wait();
            }
            _tasksQueue.push(param);
            _notEmpty.cond_singal();
        }
    }

    Task* pop_task(){
        {
            MutexLockGuard lk(_mutexLock);
            while(Empty()){
                _notEmpty.cond_wait();
            }
            Task* temp = _tasksQueue.front();
            _tasksQueue.pop();
            return temp;
        }
    }
    
    Task* get_task(){
        {
            MutexLockGuard lk(_mutexLock);
            if(!Empty())
                return _tasksQueue.front();
            else
                return nullptr;
        }
    }
};

#endif // __TASK_QUEUE_HPP__