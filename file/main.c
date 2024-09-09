#include "my_file.h"

int main(){
  FILE_* fp = fopen_("./log.txt", "w");
  
  const char* ptr = "hello world\n";
  fwrite_(ptr, strlen(ptr), fp);
  
  fclose_(fp);

  return 0;
}
