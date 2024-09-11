#include <stdio.h>

int main(int argc, char* argv[], char* env[]){

// Method 1
// Through the command-line arguments
  printf("***************** env ******************\n");
  printf("************* Method 1 *******************");
  for(int i = 0; env[i]; ++i){
    printf("env[%d] = %s\n", i, env[i]);
  }

// Method 2
// Through the third-party vatiable -- environ
  printf("************* Method 2 *******************");
  extern char** environ;
  for(int i = 0; environ[i]; ++i){
    printf("environ[%d] = %s\n", i, environ[i]);
  }

//  printf("***********argv*********\n");
//  for(int i = 0; i < argc; ++i){
//    printf("argv[%d] = %s\n", i, argv[i]);
//  }

  return 0;
}
