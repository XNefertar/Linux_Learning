#ifndef _RING_QUEUE_HPP
#define _RING_QUEUE_HPP

#include <iostream>
#include <vector>
#include <cassert>
#include <semaphore.h>
#include <pthread.h>
#include "task_handler.hpp"
#include "lock_guard.hpp"

// const int max_size = 10;

template<typename T>
class Ring_Queue{
// PV原语
private:
    // 资源申请
    void P(sem_t& sem){
        int n = sem_wait(&sem);
        assert(n == 0);
        (void)n;
    }

    // 资源释放
    void V(sem_t& sem){
        int n = sem_post(&sem);
        assert(n == 0);
        (void)n;
    }

// 资源初始化
private:
    // 最大容量
    int _capacity;
    // 消费者信号量 —— 资源信号量
    sem_t _data_sem;
    // 生产者信号量 —— 空间信号量
    sem_t _space_sem;
    
    int _consumer_step;
    int _producer_step;

    // 模拟环形列表
    std::vector<T> _donut_list;
    pthread_mutex_t _producer_mutex;
    pthread_mutex_t _consumer_mutex;

public:
    Ring_Queue(int capacity = 10)
        :_capacity(capacity)
    {
        _donut_list.resize(capacity);

        assert(0 == sem_init(&_space_sem, 0, _capacity));
        assert(0 == sem_init(&_data_sem, 0, 0));

        pthread_mutex_init(&_producer_mutex, nullptr);
        pthread_mutex_init(&_consumer_mutex, nullptr);

        _consumer_step = _producer_step = 0;

    }


    // 具体操作：消费 + 生产

    // 生产者
    void Push(const T& in){
        // 申请空间信号量
        P(_space_sem);
        // 成功，加锁
        lock_guard _lock(&_producer_mutex);
        _donut_list[_producer_step++] = in;
        _producer_step %= _capacity;

        // 释放消费者信号量
        V(_data_sem);
    }


    // 消费者
    void Pop(T* out){
        P(_data_sem);
        lock_guard _lock(&_consumer_mutex);
        *out = _donut_list[_consumer_step++];
        // (*out)();
        _consumer_step %= _capacity;

        V(_space_sem);
    }


    ~Ring_Queue(){
        sem_destroy(&_data_sem);
        sem_destroy(&_space_sem);

        pthread_mutex_destroy(&_consumer_mutex);
        pthread_mutex_destroy(&_producer_mutex);
    }

};




#endif