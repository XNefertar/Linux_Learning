#include <iostream>
#include <vector>
#include <memory>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "lock_guard.hpp"

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int tickets = 1000;

void* start_routine(void* args){
    const char* str = static_cast<const char*>(args);
    while(1){
        lock_guard lock(&mtx);
        // pthread_mutex_lock(&mtx);
        pthread_cond_wait(&cond, &mtx);
        if(tickets > 0){
            std::cout << "tickets has been taken by " << str <<  "... the rest : " << tickets-- << std::endl;
            // pthread_mutex_unlock(&mtx);
        }
        else{
            break;
        }
        // pthread_mutex_unlock(&mtx);
    }
}
std::vector<pthread_t> tid_vec;

int main(){
    for(int i = 0; i < 10; ++i){
        pthread_t tid{};
        char* name_buffer = new char[1024]{};
        snprintf(name_buffer, 1024, "thread:%d", i + 1);
        pthread_create(&tid, nullptr, start_routine, name_buffer);
        tid_vec.push_back(tid);
    }
    while(1){
        sleep(1);
        pthread_cond_signal(&cond);
    }

    for(auto& it : tid_vec){
        pthread_join(it, nullptr);
    }
    std::cout << "exit success, join success." << std::endl;


    return 0;
}