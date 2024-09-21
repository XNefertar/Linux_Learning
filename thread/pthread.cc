#include <iostream>
#include <pthread.h>
#include <unistd.h>

int count = 0;

void* func_handler(void* name){
    while(1){
        std::cout << "This is the new thread..." << "  " << "and the count = " << count++ << " and the name pthread = " << (char*)name << std::endl;
        std::cout << "----------------------------------------------------------------------" << std::endl;
        sleep(1); 
    }
}

int main(){

    pthread_t tid;
    int n = pthread_create(&tid, nullptr, func_handler, (void*)"X_pthread");

    while(1){
        std::cout << "This is the main thread..." << "  " << "and the count = " << count << " and the tid pthread = "  << "0x" << std::hex << tid << std::oct << std::endl;
        sleep(1);
    }

    return 0;
}