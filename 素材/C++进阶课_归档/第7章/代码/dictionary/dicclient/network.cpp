#include "client.hpp"
#include <stdexcept> //异常处理类

// 构造函数的定义
DictClient::DictClient(const string &ip, int port) : sockfd_(-1), is_logged_in_(false)
{
    // 完成网络的连接功能
    if (!connectToServer(ip, port))
    {
        throw runtime_error("connect to server error");
    }
}

// 析构函数
DictClient::~DictClient()
{
    // 判断客户端是否存在
    if (sockfd_ >= 0)
    {
        doQuit();       // 退出用户
        close(sockfd_); // 关闭套接字
    }
}

// 网络连接函数的定义
bool DictClient::connectToServer(const string &ip, int port)
{
    // 创建通信的套接字文件描述符
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ < 0)
    {
        perror("socket error");
        return false;
    }

    // 设置端口号快速重用
    int opt = 1;
    if (setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt error");
        return false;
    }

    // 连接服务器
    sockaddr_in sin;                             // 服务器地址信息结构体
    sin.sin_family = AF_INET;                    // 通信域
    sin.sin_port = htons(port);                  // 端口号
    sin.sin_addr.s_addr = inet_addr(ip.c_str()); // ip地址

    // 连接服务器
    if (connect(sockfd_, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("connect error");
        return false;
    }

    return true;
}
