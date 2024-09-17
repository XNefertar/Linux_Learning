#include "comm.hpp"

// 命名管道读取端

int main()
{
    // open_named_piped(PATH_NAME_PIPE);

    // sleep(10);
    // std::cout << "named_pipe is build?" << std::endl;
    // sleep(10);

    umask(0);
    int fd{};
    do{    
        fd = open(PATH_NAME_PIPE, O_RDONLY, 0666);
        if(fd == -1) std::cout << "waiting file open..." << std::endl;
        else std::cout << "fd = " << fd << std::endl;
        sleep(1);
    }while(fd == -1);

    key_t key = get_key();
    printf("key: 0x%x\n", key);
    sleep(3);

    // int shm_id = shmget(key, MAX_SIZE, IPC_CREAT);
    // std::cout << "shm_id = " << shm_id << std::endl;
    // if (shm_id == -1) {
    //     std::cout << "del_shm is called" << std::endl;
    //     del_shm(shm_id);  // 删除已有的共享内存
    // }

    // 创建新的共享内存
    int shm_id = get_shm(key);
    printf("shmid: %d\n", shm_id);

    
    char* start = (char*)attachShm(shm_id); 
    for(int i = 0; i < 24; ++i){
        std::cout << "server is reading..." << std::endl;
        std::cout << "start: " << start <<  std::endl;
        // int target = 0;
        // ssize_t s = read(fd, &target, sizeof(int));
        // if(target == 1) std::cout << "start: " << start << std::endl;
        sleep(1);
    }
    
    rm_process(PATH_NAME_PIPE);

    detach_shm(start);
    sleep(5);
    del_shm(shm_id);

    return 0;
}