#include "Thread_Class.hpp"

Thread::Thread()
    : _thID(0),
      _isRunning(false)
{}

void* Thread::ThreadFunc(void* args){
    Thread* temp = static_cast<Thread*>(args);
    if(temp){
        temp->run();
    }
    return nullptr;
}

void Thread::thread_start(){
    pthread_create(&_thID, nullptr, ThreadFunc, this);
}
void Thread::thread_join(){
    pthread_join(_thID, nullptr);
}

WorkThread1::WorkThread1(ThreadPool& pool)
    : _pool(pool)
{}

void WorkThread1::run(){
    _pool.exec_task();
}
