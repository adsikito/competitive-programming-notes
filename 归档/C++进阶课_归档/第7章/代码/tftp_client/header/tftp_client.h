#ifndef TFTP_CLIENT_H
#define TFTP_CLIENT_H

// 引入头文件
#include <myhead.h>
#include <errno.h>

// 封装一个客户端类
class TFTPClient
{
private:
    static const int PORT = 6666;       // 服务器端口号
    static const int BUFFER_SIZE = 516; // 协议包的大小

    int sfd;                        // 客户端套接字
    struct sockaddr_in server_addr; // 服务器地址信息结构体

    // 该客户端提供的私有的成员函数
    int doDownload();    // 下载函数
    int doUpload();      // 上传函数
    void clearScream();  // 清屏函数
    void waitForInput(); // 等待输入函数
    void showMenu();     // 展示菜单函数

public:
    TFTPClient(const string &serverIP); // 构造函数
    ~TFTPClient();                      // 析构函数

    void run(); // 客户端执行函数
};

#endif