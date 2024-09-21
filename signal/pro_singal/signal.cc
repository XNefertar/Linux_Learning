#include <iostream>
#include <signal.h>
#include <unistd.h>


void handler(int num){
    int cnt = 10;
    while(cnt--){
        std::cout << "倒数 " << cnt << " 秒: " << std::endl; 
        std::cout << "捕捉到了" << num << "号信号，正在处理..." << std::endl;
        sleep(1);
    }
    std::cout << "任务处理结束，即将退出..." << std::endl;
    sleep(1);
    exit(1);
}

int main(){
    signal(SIGINT, handler);
    while(1){
        std::cout << "正在执行任务..." << std::endl;
        sleep(1);
    }
    return 0;
}