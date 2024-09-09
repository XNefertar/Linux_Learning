#include "my_file.h"



FILE_* fopen_(const char* path_name, const char* mode){
  int default_mode = 0666;
  int fd = 0;
  int flag = 0;

  if(strcmp(mode, "r") == 0){
    flag |= (O_RDONLY);
    fd = open(path_name, flag);
  }

  else if(strcmp(mode, "w") == 0){
    flag |= (O_WRONLY | O_CREAT | O_TRUNC);
    fd = open(path_name, flag, default_mode);
  }

  else if(strcmp(mode, "a") == 0){
    flag |= (O_WRONLY | O_CREAT | O_APPEND);
    fd = open(path_name, flag, default_mode);
  }

  else{
      // TODO
  }
  
  if(fd < 0){
    const char* err = strerror(errno);
    write(2, err, strlen(err));
    return NULL;
  }


#ifdef DEBUG
  printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
  printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
  printf("this is a test programa!!!\n");
  printf("The mode is %s\nThe path name is %s\n", mode, path_name);
  printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
  printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
#endif



  FILE_* fp = (FILE_*)(malloc(sizeof(FILE_)));
  fp->fileno = fd;
  fp->flags = SYNC_LINE;
  fp->capacity = SIZE;
  fp->size = 0;
  memset(fp->buffer, 0, SIZE);

  return fp;
}


void fflush_(FILE_* fp){
  write(fp->fileno, fp->buffer, fp->size);
}


void fwrite_(const void* ptr, size_t num, FILE_* fp){
  if(fp->capacity < (int)num + fp->size){
    fp =(FILE_*)realloc(fp, num + fp->capacity);
  }
  memcpy(fp->size + fp->buffer, ptr, num);

  fp->size += num;


  if(fp->flags & SYNC_NOW){
    fflush_(fp);
  }

  else if(fp->flags & SYNC_LINE){
    for(int i = 0; i < fp->size; ++i){
      if(fp->buffer[i] == '\n'){
        fp->size = i + 1;
        fflush_(fp);
      }
    }
  }

  else if(fp->flags & SYNC_FULL){
    if(fp->size == fp->capacity){
      fflush_(fp);
    } 
  }

  fp->size = 0;
}


void fclose_(FILE_* fp){
  close(fp->fileno);
#ifdef DEBUG 
  printf("File close success!\n");
#endif
}
