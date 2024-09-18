#include <iostream>
#include <unistd.h>
#include <sys/types.h>

int main(){
  int cnt = 0;
  while(true){
    std::cout << "pid = " << getpid() << ", cnt = " << cnt++ << std::endl;
    sleep(1);
  }



  return 0;
}
