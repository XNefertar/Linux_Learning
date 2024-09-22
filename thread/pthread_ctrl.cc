#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <stdio.h>


#define NUM_THREAD 10
// using func_ptr = void*(*)(void*);
// std::vector<func_ptr> vec;

class ThreadData{
public:
    int number;
    pthread_t tid;
    char name[1024];
};

std::vector<ThreadData*> threads;

void* func_handler(void* tmp){
    ThreadData* td = static_cast<ThreadData*>(tmp);
    int cnt = 10;
    while(cnt){
        // std::cout << "cnt " << cnt << "&cnt" << &cnt << std::endl;
        std::cout << "new thread create succeess, name = " << td->name << ", cnt = " << cnt-- << std::endl;
        // std::cout <<  "  " << " the name pthread = " << ((ThreadData*)td)->name << std::endl;
        sleep(1); 
    }
    return nullptr;
}

int main(){

    for(int i = 0; i < NUM_THREAD; ++i){
        ThreadData* td = new ThreadData{};
        td->number = i + 1;
        snprintf(td->name, sizeof(td->name), "thread : %d", i);
        pthread_create(&td->tid, nullptr, func_handler, (void*)td);

        threads.push_back(td);
        // sleep(1);
    }

    // 主线程打印新建线程信息
    for(auto it : threads){
        std::cout << "create thread: " << it->name << " : " << it->tid << " success" << std::endl;
    }

    // 主线程集中结束新建线程
    for(auto it : threads){
        pthread_join(it->tid, nullptr);
        std::cout << it->name << " join success." << std::endl;
    }

    // sleep(5);
    while(1){
        sleep(1);
        std::cout << "This is the main thread..." << std::endl;
        // sleep(1);
    }

    return 0;
}