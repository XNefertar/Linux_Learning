#include "Thread.hpp"

// 信息打印时会发生错乱
// 需要添加互斥锁加以约束
// TODO
void* test(void* args){
    const char* str = static_cast<const char*>(args);
    std::cout <<  "str = " << str << std::endl;
    return nullptr;
}

// 封装Thread
// 实现类C++线程接口

int main(){
    Thread t1(1, test, (void*)"hello C world!");
    Thread t2(2, test, (void*)"hello CPP world!");
    Thread t3(3, test, (void*)"hello Java world!");
    Thread t4(4, test, (void*)"hello Linux world!");
    Thread t5(5, test, (void*)"hello Python world!");
    // sleep(1);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    
    return 0;
}