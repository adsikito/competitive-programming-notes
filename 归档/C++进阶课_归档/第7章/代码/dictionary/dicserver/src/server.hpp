#ifndef SERVER_HPP
#define SERVER_HPP

#include "database_manager.hpp" //数据库相关头文件
#include <memory>               //智能指针头文件
#include <myhead.h>

// 定义电子词典服务器类
class Server
{
public:
    // 构造函数：需要使用数据库管理对象、ip地址、端口号进行构造一个服务器
    Server(shared_ptr<DatabaseManager> db_manager, const string ip, int port);
    ~Server(); // 析构函数

    // 启动服务器
    bool start();
    // 停止服务器
    bool stop();

private:
    int sfd_;                                // 服务器套接字文件描述符
    int port_;                               // 端口号
    string ip_;                              // ip地址
    bool running_;                           // 运行标识
    shared_ptr<DatabaseManager> db_manager_; // 数据库管理器

    // 处理客户端函数
    void handleClient(int cfd, sockaddr_in client_addr);

    // 提供一个获取当前系统时间的函数
    static string getCurrentTime();
};

#endif