#include <iostream>
#include <signal.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    if(argc < 3){
        std::cout << "Usge: pid signo..." << std::endl;
        exit(1);
    }
    pid_t id = atoi(argv[1]);
    int signo = atoi(argv[2]);

    kill(id, signo);
    return 0;
}