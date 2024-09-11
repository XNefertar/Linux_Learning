#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>

int a = 10;

int main(){
  pid_t pid = fork();
  assert(pid >= 0);
  if(pid == 0){
    printf("child a = %d\n", a);
  }
  else{
    a = 100;
    printf("parent a = %d\n", a);
  }

  return 0;
}

