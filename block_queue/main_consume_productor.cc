#include "block_queue.hpp"
#include "task_handler.hpp"

const std::string operator_set = "+-*/";

// 计算 + 存储
template<class calculate, class save>
class Block_Queues{
public:
    Block_Queue<Cal_Task>* _calculate_bq;
    Block_Queue<Save_Task>* _save_bq;
};

template<class T>
void* producer_func(void* _bq){

    Block_Queue<Cal_Task>* bq = static_cast<Block_Queues<Cal_Task, Save_Task>*>(_bq)->_calculate_bq;    
    while(1){
        int x = rand() % 100 + 1;
        int y = rand() % 10;
        int operator_code = rand() % operator_set.size();
        

        Cal_Task _cal_task(x, y, operator_set[operator_code], mymath);
        bq->push(_cal_task);
        std::cout << "生产任务: " << _cal_task.to_string() << std::endl;
        sleep(1);
    }
    return nullptr;
}


template<class T>
void* consumer_func(void* _bq){
    Block_Queue<Cal_Task>* bq = static_cast<Block_Queues<Cal_Task, Save_Task>*>(_bq)->_calculate_bq;
    Block_Queue<Save_Task>* save_bq = static_cast<Block_Queues<Cal_Task, Save_Task>*>(_bq)->_save_bq;
    while(1){
        // 从共享区抓取任务并执行
        Cal_Task _cal_task;
        bq->pop(&_cal_task);
        std::string result = _cal_task();
        std::cout << "消费任务: " << result << std::endl;
        result += '\n';


        // 向存储任务内写入
        Save_Task _save_task(result, _save);
        save_bq->push(_save_task);
        std::cout << "推送任务完成..." << std::endl;
        sleep(1);
    }
    return nullptr;
}


template<class T>
void* save_func(void* _bq){
    // Block_Queue<Save_Task>* _save_task = static_cast<Block_Queues<Cal_Task, saver>*>(_bq)->_save_bq;

    Block_Queue<Save_Task> *save_bq = (static_cast<Block_Queues<Cal_Task, Save_Task> *>(_bq))->_save_bq;

    while(true){
        Save_Task t;
        save_bq->pop(&t);
        t();
        std::cout << "保存任务：完成..." << std::endl; 
    }
    return nullptr;

}


int main(){

    srand((unsigned long)time(nullptr) ^ getpid());

    pthread_t producer_tid;
    pthread_t consumer_tid;
    pthread_t saver_tid;

    Block_Queues<Cal_Task, Save_Task> bqs;
    bqs._calculate_bq = new Block_Queue<Cal_Task>();
    bqs._save_bq = new Block_Queue<Save_Task>();

    pthread_create(&producer_tid, nullptr, producer_func<int>, &bqs);
    pthread_create(&consumer_tid, nullptr, consumer_func<int>, &bqs);
    pthread_create(&saver_tid, nullptr, save_func<int>, &bqs);


    // delete bq;
    pthread_join(producer_tid, nullptr);
    pthread_join(consumer_tid, nullptr);
    pthread_join(saver_tid, nullptr);


    return 0;
}
