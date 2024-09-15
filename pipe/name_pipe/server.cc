#include "comm.hpp"

int main(){
    bool is_success = load_process(PATH_NAME);
    if(is_success){
        std::cout << "server process is start # " << std::endl;
        int id = open(PATH_NAME, O_RDONLY, O_TRUNC);
        std::cout << "server process is ready." << std::endl;
        char buffer[1024]{};
        while(1){
            ssize_t t = read(id, buffer, sizeof(buffer));
            if(t > 0){
                buffer[strlen(buffer)] = 0;
                std::cout << "client : " << buffer << std::endl;
            }
            else if(t == 0) {
                std::cout << "process is over at the same time." << std::endl; 
                break;
            }
            else break;
            memset(buffer, 0, sizeof buffer);
        }
    }
    else std::cout << "errno : " << errno << " err messege : " << strerror(errno) << std::endl;

    rm_process(PATH_NAME);
    return 0;
}