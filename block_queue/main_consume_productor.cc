#include "block_queue.hpp"

void* producer_func(void* _bq){
    Block_Queue* bq = static_cast<Block_Queue*>(_bq);
    while(1){
        int in = rand() % 10 + 1;
        bq->push(in);
        std::cout << "生产任务: " << in << std::endl;
        // sleep(1);
    }
    return nullptr;
}


void* consumer_func(void* _bq){
    Block_Queue* bq = static_cast<Block_Queue*>(_bq);
    while(1){
        int* out = new int{};
        bq->pop(out);
        std::cout << "消费任务: " << *out << std::endl;
        sleep(1);
    }
    return nullptr;
}

int main(){
    srand((unsigned long)time(nullptr) ^ getpid());

    pthread_t producer_tid;
    pthread_t consumer_tid;
    Block_Queue* bq = new Block_Queue{};

    pthread_create(&producer_tid, nullptr, producer_func, bq);
    pthread_create(&consumer_tid, nullptr, consumer_func, bq);

    // delete bq;
    pthread_join(producer_tid, nullptr);
    pthread_join(consumer_tid, nullptr);

    return 0;
}
