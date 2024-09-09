#pragma once

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>
#include <assert.h>
#include <errno.h>


// 按照缓冲区的刷新方式定义宏
#define SIZE 1024
#define SYNC_NOW 1
#define SYNC_LINE 2
#define SYNC_FULL 4

// 定义FILE结构体
// 内部存在缓冲区
typedef struct FILE_{
  int fileno;        // 文件描述符
  int flags;         // 标识缓冲区刷新规则
  char buffer[SIZE]; // 缓冲区 
  int size;       // 实际缓冲区存储的数据
  int capacity;   // 缓冲区最大容量

}FILE_;


FILE_* fopen_(const char* path_name, const char* mode);
void fwrite_(const void* ptr, size_t num, FILE_* fp);
void fclose_(FILE_* fp);

