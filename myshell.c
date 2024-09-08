#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <string.h>

#define NUM 1024
#define OPT_NUM 64


char lineCommand[NUM];
char* myargv[OPT_NUM];

int main(){
  while(1){
    printf("[用户名@主机名 当前路径] # ");
    fflush(stdout);

    char* s = fgets(lineCommand, sizeof(lineCommand) - 1, stdin);

    assert(s != NULL);
    (void)s;
    lineCommand[strlen(lineCommand) - 1] = 0;

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
      execvp(myargv[0], myargv);
      exit(0);
    }
  
    waitpid(id, NULL, 0); 
  }

  return 0;
}
