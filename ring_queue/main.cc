#include <functional>
#include <pthread.h>
#include <sys/types.h>
#include "task_handler.hpp"
#include "ring_queue.hpp"

// using func_ptr = std::function<int(int, int, char)>;
const std::string operator_set = "+-*/";

template<typename T>
void* producer_func(void* args){
    Ring_Queue<Task>* _rg = static_cast<Ring_Queue<Task>*>(args);
    while(1){
        int x = rand() % 100 + 1;
        int y = rand() % 10;
        int operator_code = rand() % operator_set.size();
        Task _task(x, y, operator_set[operator_code], mymath);
        _rg->Push(_task);
        std::cout << "生产任务: " << _task.to_string() << std::endl;
        sleep(1);
    }
    return nullptr;
}

template<typename T>
void* consumer_func(void* args){
    Ring_Queue<Task>* _rg = static_cast<Ring_Queue<Task>*>(args);
    while (1){

        Task _task;
        _rg->Pop(&_task);

        // std::cout << "this is a test..." << std::endl;
        // sleep(5);

        std::cout << "消费任务: " << _task() << std::endl;
        // sleep(1);
    }

    return nullptr;
}


int main(){
    srand((unsigned long)time(nullptr) ^ getpid());

    pthread_t consumer_tid;
    pthread_t producer_tid;

    Ring_Queue<Task> _ring_queue;
    pthread_create(&consumer_tid, nullptr, consumer_func<Task>, &_ring_queue);
    pthread_create(&producer_tid, nullptr, producer_func<Task>, &_ring_queue);


    pthread_join(consumer_tid, nullptr);
    pthread_join(producer_tid, nullptr);
    return 0;
}