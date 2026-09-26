#ifndef TFTP_SERVER_H
#define TFTP_SERVER_H
#include <myhead.h>

// 创建服务器类
class TFTPServer
{
private:
    static const int PORT = 6666;       // 服务器的端口号
    static const int BUFFER_SIZE = 516; // 数据包的最大容量

    int sfd;                        // 服务器套接字文件描述符
    struct sockaddr_in server_addr; // 服务器地址信息结构体
    string root_dir;                // 文件服务的根目录

    // 处理客户端的请求函数
    // const char *filename：要发送给客户端的文件名
    // client_addr:客户端地址信息结构体
    // addr_len:地址信息结构体大小
    void handleReadRequest(const char *filename, struct sockaddr_in &client_addr, socklen_t addr_len); // 处理读请求

    // char *filename：将客户端发来的数据存储到的文件
    // client_addr:客户端地址信息结构体
    // addr_len:地址信息结构体大小
    void handleWriteRequest(const char *filename, struct sockaddr_in &client_addr, socklen_t addr_len); // 处理写请求

    // const char * msg：要发送给客户端的错误信息
    // client_addr:客户端地址信息结构体
    // addr_len:地址信息结构体大小
    void sendError(const char *msg, struct sockaddr_in &client_addr);

public:
    TFTPServer(const string &root = "."); // 构造函数的声明
    ~TFTPServer();                        // 析构函数的声明

    void run(); // 启动服务器的函数
};

#endif