// #include <iostream>
// #include <stdio.h>
// #include <fcntl.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <string>
// #include <unistd.h>
// #include <cstring>

// int main(){
//     std::string s = "/home/xl/code/repositories/linux_learning/pipe/test/file.txt";

//     char w_buffer[1024];
//     fgets(w_buffer, sizeof(w_buffer), stdin);
//     int id = open(s.c_str(), O_WRONLY);
//     ssize_t w1 = write(id, w_buffer, strlen(w_buffer));  // 使用实际的字符串长度进行写入
//     w_buffer[strlen(w_buffer) - 1] = 0;
//     std::cout << "w_buffer = " << w_buffer << std::endl;
//     std::cout << "num of element = " << strlen(w_buffer) << std::endl;
//     close(id);


//     int r_id = open(s.c_str(), O_RDONLY);
//     char r_buffer[1024];
//     ssize_t r1 = read(r_id, r_buffer, sizeof(r_buffer));
//     r_buffer[strlen(r_buffer) - 1] = 0;

//     std::cout << "r_buffer = " << r_buffer << std::endl;
//     std::cout << "num of element = " << strlen(r_buffer) << std::endl;
//     std::cout << "last code is = " << (int)r_buffer[strlen(r_buffer) - 1] << std::endl;
    
//     return 0;
// }


#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int main() {
    // 文件路径
    std::string s = "/home/xl/code/repositories/linux_learning/pipe/test/file.txt";

    // 写入缓冲区
    char w_buffer[1024];
    std::cout << "Enter text to write to the file: ";
    fgets(w_buffer, sizeof(w_buffer), stdin);

    w_buffer[strlen(w_buffer) - 1] = 0; // 去掉换行符
    // 打开文件，确保文件存在，使用读写模式
    int id = open(s.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (id == -1) {
        perror("打开文件失败");
        return 1;
    }

    // std::cout << "w_buffer = " << w_buffer << std::endl;
    // std::cout << "num of element = " << strlen(w_buffer) << std::endl;
    // 写入文件，写入实际的字符串长度
    ssize_t w1 = write(id, w_buffer, strlen(w_buffer));
    if (w1 == -1) {
        perror("写入文件失败");
        close(id);
        return 1;
    }

    // 输出写入的内容
    std::cout << "w1 = " << w1 << std::endl;
    std::cout << "w_buffer = " << w_buffer << std::endl;
    std::cout << "num of element = " << strlen(w_buffer) << std::endl;

    // 关闭文件
    close(id);

    // 打开文件以进行读取
    int r_id = open(s.c_str(), O_RDONLY);
    if (r_id == -1) {
        perror("打开文件失败");
        return 1;
    }

    // 读取缓冲区
    char r_buffer[1024];
    memset(r_buffer, 0, sizeof(r_buffer)); // 清空缓冲区
    ssize_t r1 = read(r_id, r_buffer, sizeof(r_buffer) - 1);
    if (r1 == -1) {
        perror("读取文件失败");
        close(r_id);
        return 1;
    }

    // 确保读取的数据以 '\0' 结尾
    r_buffer[r1] = '\0';
    std::cout << "r1 = " << r1 << std::endl;
    // 输出读取的内容
    std::cout << "r_buffer = " << r_buffer << std::endl;
    std::cout << "num of element = " << strlen(r_buffer) << std::endl;
    std::cout << "last code is = " << (int)r_buffer[strlen(r_buffer) - 1] << std::endl;

    // 关闭文件
    close(r_id);

    return 0;
}
