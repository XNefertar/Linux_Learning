#include <memory>
#include "TaskQueue.hpp"
#include "Thread_PC.hpp"

int main()
{
    TaskQueue tq(10);
    std::unique_ptr<Thread> ProducerPtr(new Producer(tq));
    std::unique_ptr<Thread> ConsumerPtr(new Consumer(tq));

    ProducerPtr->start();
    ConsumerPtr->start();

}