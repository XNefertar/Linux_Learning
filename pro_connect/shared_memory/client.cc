#include "comm.hpp"
// 传入数据端

// 加入信号传送功能
// 命名管道写入端
int main()
{
    open_named_piped(PATH_NAME_PIPE);
    umask(0);
    int fd = open(PATH_NAME_PIPE, O_WRONLY | O_TRUNC, 0666);

    key_t key = get_key();
    printf("key: 0x%x\n", key);


    int shm_id = get_shm(key);
    printf("shmid: %d\n", shm_id);

    
    char* start = (char*)attachShm(shm_id);

    // int flag = 1;

    int cnt = 0;

    for(int i = 0; i < 24; ++i){
        snprintf(start, MAX_SIZE, "This is a client process[%d] is connecting with you, num_code[%d]", shm_id, ++cnt);
        // ssize_t s = write(fd, &flag, sizeof(int));
        sleep(1);
    }
    
    // rm_process(PATH_NAME_PIPE);
    detach_shm(start);
    return 0;
}