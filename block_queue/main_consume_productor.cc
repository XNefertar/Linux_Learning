#include "block_queue.hpp"
#include "task_handler.hpp"

const std::string operator_set = "+-*/";

template<typename T>
void* producer_func(void* _bq){
    Block_Queue<Task>* bq = static_cast<Block_Queue<Task>*>(_bq);
    while(1){
        int x = rand() % 100 + 1;
        int y = rand() % 10;
        int operator_code = rand() % operator_set.size();
        Task _task(x, y, operator_set[operator_code], mymath);
        bq->push(_task);
        std::cout << "生产任务: " << _task.to_string() << std::endl;
        sleep(1);
    }
    return nullptr;
}


template<typename T>
void* consumer_func(void* _bq){
    Block_Queue<Task>* bq = static_cast<Block_Queue<Task>*>(_bq);
    while(1){
        Task _task;
        bq->pop(&_task);
        std::cout << "消费任务: " << _task() << std::endl;
        // sleep(1);
    }
    return nullptr;
}


int main(){
    srand((unsigned long)time(nullptr) ^ getpid());

    pthread_t producer_tid;
    pthread_t consumer_tid;
    Block_Queue<Task>* bq = new Block_Queue<Task>{};

    pthread_create(&producer_tid, nullptr, producer_func<int>, bq);
    pthread_create(&consumer_tid, nullptr, consumer_func<int>, bq);

    // delete bq;
    pthread_join(producer_tid, nullptr);
    pthread_join(consumer_tid, nullptr);

    return 0;
}
