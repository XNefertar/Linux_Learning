#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <string>
#include "lock_guard.hpp"

pthread_mutex_t mtx;
int tickets = 10000;

// Q —— 为什么这里一直是一个线程在执行任务
// A —— 对于第一个获取锁的线程，当它释放锁后，又立即进入获取锁的状态
// 且由于调度策略，其获取锁较其他线程更为容易，所以出现了一个线程一直执行任务的情况
// 如何解决？ —— 在完成一次任务后，进行休眠，模拟后续的操作，即可解决上述问题
void* get_tickets(void* args){
    const char* str = static_cast<const char*>(args);
    // 测试
    // start
    //
    // while(1) {
    //     std::cout << str << ' ';
    //     std::cout << "&buffer" << args << std::endl;
    // }
    //
    // end

    while(1){
        // pthread_mutex_lock(&mtx);
        lock_guard lock(&mtx);

        if(tickets > 0){
            usleep(100);
            std::cout << str << " has got a ticket... " << "left: " << tickets-- << std::endl;
            // pthread_mutex_unlock(&mtx);
        }
        else{
            // pthread_mutex_unlock(&mtx);
            break;
        }
        usleep(1000);
    }

}

std::vector<pthread_t> vec_tid;

int main(){
    // 创建tid列表
    // 用于后续join线程
    
    // 为什么不用普通的栈变量
    // 因为函数栈帧的变量创建规律
    // 栈上创建数组，它的地址是一样的！！！
    // 这样会导致数据覆盖的问题！！！
    for(int i = 0; i < 5; ++i){
        usleep(1000);
        pthread_t tid;
        char* buffer = new char[1024]{};
        snprintf(buffer, 1024, "thread:%d", i);
        pthread_create(&tid, nullptr, get_tickets, buffer);
        vec_tid.push_back(tid);
        // delete[] buffer;
    }

    // for (int i = 0; i < 5; ++i){
    //     pthread_t tid;
    //     char *buffer = new char[1024]; // 动态分配内存
    //     snprintf(buffer, 1024, "thread:%d", i);
    //     pthread_create(&tid, nullptr, get_tickets, buffer);
    //     vec_tid.push_back(tid);
    // }

    // 线程合并
    for(auto& it : vec_tid){
        pthread_join(it, nullptr);
    }

    return 0;
}