#pragma once
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#define PATH_NAME "/home/xl/code/repositories/linux_learning/pipe/name_pipe/TEST"

bool load_process(std::string path_name)
{
    umask(0);
    int s = mkfifo(path_name.c_str(), 0666);
    if(s == 0) return true;
    else return false;
}

void rm_process(std::string path_name)
{
    ssize_t s = unlink(path_name.c_str());
    if (s == 0)
        std::cout << "process is unlink..." << std::endl;
    else
        std::cout << "errno : " << errno << " err messege : " << strerror(errno) << std::endl;
}