#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <stdio.h>


#define NUM_THREAD 10
// using func_ptr = void*(*)(void*);
// std::vector<func_ptr> vec;

// 记录线程信息
class ThreadData{
public:
    int number;
    pthread_t tid;
    char name[1024];
};

// 保存线程退出信息
class ExitData{
public:
    int exit_code;
};

std::vector<ThreadData*> threads;

void* func_handler(void* tmp){
    ThreadData* td = static_cast<ThreadData*>(tmp);
    int exit_code = 111;

    // 需要注意注释部分的错误
    // 因为返回了一个栈上的资源
    // 导致在函数作用域结束后，资源被自动释放
    // 导致资源丢失，打印失败
    // 而采用指针返回，则只是返回一个地址拷贝数据
    // 具体指向的堆上的数据则不会被清理
    // 从而可以正确打印
    ExitData* ed = new ExitData();
    ed->exit_code =  117;
    int cnt = 10;
    while(cnt){
        // 每个线程都独立拥有一个栈区
        // 对于其中创建的局部变量
        // 其他线程无法访问
        // 该栈区可认为是独立的
        // 就如这里的cnt局部变量一样
        std::cout << "cnt " << cnt << "&cnt" << &cnt << std::endl;
        std::cout << "new thread create succeess, name = " << td->name << ", cnt = " << cnt-- << std::endl;
        // std::cout <<  "  " << " the name pthread = " << ((ThreadData*)td)->name << std::endl;
        sleep(1); 
    }

    return ed;
    // return &exit_code;
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
        // int* ret{};
        ExitData* tmp_ed = new ExitData();
        pthread_join(it->tid, (void**)&tmp_ed);
        std::cout << it->name << " join success, " << "the exit code is " << tmp_ed->exit_code << std::endl;
    }

    // sleep(5);
    while(1){
        sleep(1);
        std::cout << "This is the main thread..." << std::endl;
        // sleep(1);
    }

    return 0;
}