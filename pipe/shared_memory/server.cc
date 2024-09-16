#include "comm.hpp"

int main()
{
    key_t key = get_key();
    printf("key: 0x%x\n", key);


    int shm_id = creat_shm(key);
    printf("shmid: %d\n", shm_id);


    char* start = (char*)attachShm(shm_id); 
    for(int i = 0; i < 10; ++i){
        std::cout << "start: " << start << std::endl;
        sleep(1);
    }


    detach_shm(start);
    sleep(10);
    del_shm(shm_id);

    return 0;
}