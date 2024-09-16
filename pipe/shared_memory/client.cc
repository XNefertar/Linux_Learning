#include "comm.hpp"
int main()
{
    key_t key = get_key();
    printf("key: 0x%x\n", key);
    int shm_id = get_shm(key);
    printf("shmid: %d\n", shm_id);
    char* start = (char*)attachShm(shm_id);

    int cnt = 0;
    for(int i = 0; i < 10; ++i){
        snprintf(start, MAX_SIZE, "This is a client process[%d] is connecting with you, num_code[%d]", shm_id, ++cnt);
        sleep(1);
    }
    
    detach_shm(start);
    return 0;
}