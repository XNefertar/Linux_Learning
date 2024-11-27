#ifndef __TASK_HPP__
#define __TASK_HPP__
#define PARAM_TYPE  int
#define RESULT_TYPE int

class Task
{
private:
    PARAM_TYPE  _param1;
    PARAM_TYPE  _param2;
    RESULT_TYPE _result;

public:
    Task(PARAM_TYPE param1, PARAM_TYPE param2)
        : _param1(param1),
          _param2(param2)
    {}

    Task(const Task& temp){
        _param1 = temp._param1;
        _param2 = temp._param2;
        _result = temp._result;
    }

    void set_param1(const PARAM_TYPE& param1) { _param1 = param1; }
    void set_param2(const PARAM_TYPE& param2) { _param2 = param2; }
    void set_result(const PARAM_TYPE& result) { _result = result; }

    PARAM_TYPE get_param1() { return this->_param1; }
    PARAM_TYPE get_param2() { return this->_param2; }
    PARAM_TYPE get_result() { return this->_result; }
};
#endif // __TASK_HPP__