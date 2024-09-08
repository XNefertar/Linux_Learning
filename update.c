#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>


#define NUM 1024
#define OPT_NUM 64

// 宏函数的编写原则？
//
#define skip_space(str) do{\
  while(isspace(*str)) ++str;\
}while(0)


#define NONE_REDIR 0
#define INPUT_REDIR 1
#define OUTPUT_REDIR 2
#define APPEND_REDIR 3

char lineCommand[NUM];
char* myargv[OPT_NUM];
char* cwd[1024];
int redir_type = NONE_REDIR;
char* redir_file = NULL;
// 增加一个简单的重定向功能


//  为什么这里的函数无法实现空格的略过
//void skip_space(char* str){
//  while(*str == ' '){
//    ++str;
//  }
//}


void checkCommand(char* command){
  redir_file = NULL;
  redir_type = NONE_REDIR;

  assert(command);
  char* start = command;
  char* end = command + strlen(command);
  while(start != end){
    umask(0);

    if(*start == '<'){
      *start = '\0';
      start++;
      skip_space(start);
      redir_file = start;
      redir_type = INPUT_REDIR;
      break;
    }


    else if(*start == '>'){
      *start = '\0';
      start++;
      skip_space(start);
      redir_file = start;
      redir_type = OUTPUT_REDIR;
      break;
    }



    else{
      ++start;
    }
  }
}



int main(){
  while(1){
    printf("[%s@主机名 当前路径] # ", getlogin());
    fflush(stdout);

    char* s = fgets(lineCommand, sizeof(lineCommand) - 1, stdin);
    

    assert(s != NULL);
    (void)s;
    lineCommand[strlen(lineCommand) - 1] = 0;
    
    checkCommand(lineCommand);



    myargv[0] = strtok(lineCommand, " ");
    
    int i = 1;
    while((myargv[i++] = strtok(NULL, " ")));
    
    if(strcmp(myargv[0], "cd") == 0){
      chdir(myargv[1]);
      continue;
    }
#ifdef DEBUG 
    for(int j = 0; myargv[j]; ++j){
      printf("%d : %s\n", j, myargv[j]);
    }
#endif
    pid_t id = fork();
    assert(id != -1);
    

    if(id == 0){
      int fd = 0; 
      switch(redir_type){
        case INPUT_REDIR:
          {
            fd = open(redir_file, O_RDONLY);
            if(fd < 0){
              perror("wrong open");
              exit(EXIT_FAILURE);
            }
            
            break;
          }

        case OUTPUT_REDIR:
          {
            fd = open(redir_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if(fd < 0){
              perror("wrong open");
              exit(EXIT_FAILURE);
            }

            break;
          }

        case APPEND_REDIR:
          {


            break;
          }
        case NONE_REDIR:
          {
            break;
          }
        default:
          {
            perror("wrong condition");
            break;
          }

      }
      dup2(fd, redir_type);
      execvp(myargv[0], myargv);
      exit(0);
    }
  
    waitpid(id, NULL, 0); 
  }

  return 0;
}

