#ifndef __COMM_HPP_
#define __COMM_HPP_

#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cerrno>
#include <unistd.h>

#define PATH_NAME "/home/xl/code/repositories/linux_learning/pipe/shared_memory"
#define PROJECT_ID 0x1204
#define MAX_SIZE 4096

// 获取 key 值
key_t get_key(){
    key_t key = ftok(PATH_NAME, PROJECT_ID);
    if(key == -1){
        std::cerr << "key: " << errno << " : " << strerror(errno) << std::endl;
        exit(1);
    }
    return key;
}

// 获取 shmid，创建共享内存
int shm_choose(key_t key, int shm_flags){
    int ret = shmget(key, MAX_SIZE, shm_flags);
    if(ret < 0){
        std::cerr << "shm_choose: " << errno << " : " << strerror(errno) << std::endl;
        exit(1);
    }
    return ret;
}

int creat_shm(key_t key){
    return shm_choose(key, IPC_CREAT | IPC_EXCL | 0666);
}

int get_shm(key_t key){
    return shm_choose(key, IPC_CREAT | 0600);
}


void *attachShm(int shmid)
{

    void *mem = shmat(shmid, nullptr, 0); //64系统，8
    if((long long)mem == -1L)
    {
        std::cerr <<"shmat: "<< errno << ":" << strerror(errno) << std::endl;
        exit(3);
    }
    return mem;
}


void detach_shm(const void* start){
    if(shmdt(start) < 0){
        std::cerr << "detach_shm: " << errno << " : " << strerror(errno) << std::endl;
        exit(2);
    }
    std::cout << "detach success" << std::endl;
    // return shmdt(start);
}

void del_shm(int shmid){
    if(shmctl(shmid, IPC_RMID, NULL) < 0){
        std::cerr << errno << " : "  << strerror(errno) << std::endl;
        exit(3); 
    }
    std::cout << "delete success" << std::endl;
} 


#endif