#ifndef __TASK_HPP__
#define __TASK_HPP__
#define PARAM_TYPE  int
#define RESULT_TYPE int

#include <iostream>
#include <pthread.h>
class Task
{
public:
    Task() = default;
    ~Task() = default;
    virtual void process() = 0;
};

class MyTask
    : public Task
{
private:
    PARAM_TYPE _param1;
    PARAM_TYPE _param2;

public:
    virtual void process() override {
        srand(time(NULL));
        int num = rand() % 100;
        std::cout << ">> Process number " << num << std::endl;
    }

};
#endif // __TASK_HPP__