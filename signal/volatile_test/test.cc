#include <iostream>
#include <unistd.h>
#include <signal.h>
volatile int flag = 0;

void handle(int signo){
    printf("flag = %d\n", flag);
    flag = 1;
    printf("new flag = %d\n", flag);
}


int main(){
    printf("flag = %d\n", flag);
    signal(2, handle);
    while(!flag);
    printf("exit\n");
    return 0;
}