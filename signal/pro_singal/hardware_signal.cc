#include <iostream>
#include <signal.h>
#include <unistd.h>


void handler(int signo){
    int cnt = 10;
    while(cnt){
        std::cout << "段错误信号，信号编号为 " << signo << " ，已被捕捉，正在处理...  ";
        std::cout << "倒计时：" << cnt << std::endl;
        --cnt;
        sleep(1);
    }
    std::cout << "信号处理完毕，即将退出..." << std::endl;
    sleep(1);
    exit(1);
}

// 模拟野指针错误
int main(){
    signal(SIGSEGV, handler);
    std::cout << "段错误即将发生，请注意..." << std::endl;
    sleep(1);
    int* p = nullptr;
    *p = 10;
    return 0;
}