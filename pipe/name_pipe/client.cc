#include "comm.hpp"

int main(){
    int id = open(PATH_NAME, O_WRONLY, O_TRUNC);
    std::cout << "client process is ready." << std::endl;
    if(id >= 0){
        char buffer[1024]{};
        while(1){
            std::cout << "Say to server # ";
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strlen(buffer) - 1] = 0;
            ssize_t t = write(id, buffer, strlen(buffer));
            if(t == 0){
                std::cout << "no messege" << std::endl;
                break;
            }
            else if(t < 0) std::cout << "errno : " << errno << " errno msg : " << strerror(errno) << std::endl;
        }
    }
    close(id);

    return 0;
}