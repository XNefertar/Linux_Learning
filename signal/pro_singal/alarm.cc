#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int sig) {
    printf("Alarm triggered!\n");
}

int main() {
    // 注册 SIGALRM 信号处理函数
    signal(SIGALRM, alarm_handler);

    // 第一次设置闹钟为5秒
    unsigned int remaining = alarm(5);
    printf("First alarm set to 5 seconds, returned: %u seconds\n", remaining);

    // 第二次设置闹钟为2秒，验证返回之前闹钟还剩余的时间
    sleep(2);
    remaining = alarm(2);
    printf("Second alarm set to 2 seconds, returned: %u seconds\n", remaining);

    // 取消闹钟，验证返回之前还剩余的时间
    sleep(1);
    remaining = alarm(0);
    printf("Alarm canceled, returned: %u seconds\n", remaining);

    // 睡眠3秒，等待看是否会有闹钟触发
    sleep(3);

    return 0;
}
