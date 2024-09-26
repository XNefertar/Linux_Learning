#ifndef _BLOCK_QUEUE_HPP
#define _BLOCK_QUEUE_HPP

#include <iostream>
#include <queue>
#include <functional>
#include <random>
#include <unistd.h>
#include <pthread.h>
#include "lock_guard.hpp"

const int max_size = 10;

template<typename T>
class Block_Queue{
private:
    pthread_cond_t consumer_cond;
    pthread_cond_t producer_cond;
    pthread_mutex_t mtx;
    std::queue<T> _queue;
    // Task<T> _task;
public:
    // 构造函数内初始化
    Block_Queue(){
        // std::cout << "conductor function is called." << std::endl;
        pthread_cond_init(&consumer_cond, nullptr);
        pthread_cond_init(&producer_cond, nullptr);
        pthread_mutex_init(&mtx, nullptr);
    }

    // 生产任务
    void push(const T& in){
        lock_guard lk(&mtx);
        while(is_full()){
            pthread_cond_wait(&producer_cond, &mtx);
        }
        _queue.push(in);
        pthread_cond_signal(&consumer_cond);
    }

    // 消费任务
    void pop(T* out){
        lock_guard lk(&mtx);
        while(is_empty()){
            pthread_cond_wait(&consumer_cond, &mtx);
        }
        // sleep(1);
        *out = _queue.front();
        _queue.pop();
        pthread_cond_signal(&producer_cond);
    }

    // 判断
    bool is_empty(){
        return _queue.empty();
    }
    bool is_full(){
        return _queue.size() == max_size;
    }

    // 析构，销毁条件变量和互斥量
    ~Block_Queue(){
        pthread_cond_destroy(&consumer_cond);
        pthread_cond_destroy(&producer_cond);
        pthread_mutex_destroy(&mtx);
    }
};


#endif