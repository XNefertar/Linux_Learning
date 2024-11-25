#ifndef __MUTEX_LOCK_HPP__
#define __MUTEX_LOCK_HPP__

#include <pthread.h>

class MutexLock
{
private:
    pthread_mutex_t _mutex;

public:

    MutexLock(){
        pthread_mutex_init(&_mutex, nullptr);
    }
    ~MutexLock(){
        pthread_mutex_destroy(&_mutex);
    }  

    int Lock(){
        return pthread_mutex_lock(&_mutex);
    }

    int Unlock(){
        return pthread_mutex_unlock(&_mutex);
    }

    int Trylock(){
        return pthread_mutex_trylock(&_mutex);
    }

    pthread_mutex_t* GetMutexPtr(){
        return &this->_mutex;
    }
};

#endif // __MUTEX_LOCK_HPP__