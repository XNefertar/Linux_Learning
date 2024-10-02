#include "Thread_Pool.hpp"
#include "memory"

int main(){
    std::unique_ptr<Thread_pool<Cal_Task>> tp(new Thread_pool<Cal_Task>());
    
    tp->run();
    int x, y;
    char op;
    while(1)
    {
        std::cout << "请输入数据1# ";
        std::cin >> x;
        std::cout << "请输入数据2# ";
        std::cin >> y;
        std::cout << "请输入你要进行的运算#";
        std::cin >> op;
        Cal_Task t(x, y, op, mymath);
        // std::cout << "你刚刚录入了一个任务: " << t.to_string() << "， 确认提交吗？[y/n]# ";
        // char confirm;
        // std::cin >> confirm;
        // if(confirm == 'y') tp->push(t);
        tp->push(t);
        
        sleep(1);
    }

    
    return 0;
}