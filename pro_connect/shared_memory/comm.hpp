#ifndef __COMM_HPP_
#define __COMM_HPP_

#include <cassert>
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
#include <sys/stat.h>
#include <fcntl.h>

#define PATH_NAME "/home/xl/code/repositories/linux_learning/pro_connect/shared_memory"
#define PATH_NAME_PIPE "/home/xl/code/repositories/linux_learning/pro_connect/shared_memory/named_pipe"
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


void open_named_piped(std::string path_name){
    umask(0);
    int n = mkfifo(path_name.c_str(), 0666);
    // if(n < 0) std::cerr << "open_named_pipe: " << strerror(errno) << std::endl;
}


void rm_process(std::string path_name)
{
    ssize_t s = unlink(path_name.c_str());
    if (s == 0)
        std::cout << "process is unlink..." << std::endl;
    else
        std::cout << "rm_process: " << errno << " err messege : " << strerror(errno) << std::endl;
}

void detach_shm(void* start){
    if(shmdt(start) < 0){
        std::cerr << "detach_shm: " << errno << " : " << strerror(errno) << std::endl;
    }
    std::cout << "detach success" << std::endl;
}

void del_shm(int shmid){
    if(shmctl(shmid, IPC_RMID, NULL) < 0){
        std::cerr << "del_shm: " << errno << " : "  << strerror(errno) << std::endl;
    }
    std::cout << "delete success" << std::endl;
} 


// 获取 shmid，创建共享内存
int shm_choose(key_t key, int shm_flags){
    int ret = shmget(key, MAX_SIZE, shm_flags);
    if(ret < 0){
        std::cerr << "shm_choose: " << errno << " : " << strerror(errno) << std::endl;
        // del_shm(ret);
        exit(2);
    }
    return ret;
}


int get_shm(key_t key){
    umask(0);
    return shm_choose(key, IPC_CREAT | 0600);
}


int creat_shm(key_t key){
    umask(0);
    return shm_choose(key, IPC_CREAT | IPC_EXCL | 0600);
}


#endif