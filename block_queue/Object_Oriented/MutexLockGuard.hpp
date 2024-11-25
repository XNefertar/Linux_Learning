#ifndef __MUTEX_LOCK_GUARD_HPP__
#define __MUTEX_LOCK_GUARD_HPP__
#include "MutexLock.hpp"

class MutexLockGuard
{
private:
    MutexLock& _mutexLock;

public:
    MutexLockGuard(MutexLock& mutexLock)
        : _mutexLock(mutexLock)
    {
        _mutexLock.Trylock();
    }

    ~MutexLockGuard(){
        _mutexLock.Unlock();
    }
};



#endif // __MUTEX_LOCK_GUARD_HPP__