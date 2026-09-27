#include "server.hpp"  //服务器头文件
#include "message.hpp" //消息协议头文件
#include <myhead.h>
#include <time.h> //有关时间的头文件
#include <thread> //C++线程支持库

/*
    服务器的构造函数：完成套接字的创建、端口号快速重用、绑定ip和端口号
*/
Server::Server(shared_ptr<DatabaseManager> db_manager, const string ip, int port) : db_manager_(db_manager), ip_(ip), port_(port), running_(false) // 初始化列表
{
    // 创建用于连接的套接字文件描述符
    sfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd_ < 0)
    {
        throw runtime_error("socket error"); // 抛出异常
    }

    // 设置端口号快速重用
    int opt = 1;
    if (setsockopt(sfd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        close(sfd_);
        throw runtime_error("setsockopen error");
    }

    // 绑定ip地址和端口号
    sockaddr_in sin;
    sin.sin_family = AF_INET;                    // 通信域
    sin.sin_port = htons(port);                  // 端口号
    sin.sin_addr.s_addr = inet_addr(ip.c_str()); // ip地址

    if (bind(sfd_, (sockaddr *)&sin, sizeof(sin)) < 0)
    {
        close(sfd_);
        throw runtime_error("bind error");
    }
}

/*
    析构函数：停止服务器运行
*/
Server::~Server()
{
    stop();
}

/*
    启动服务器函数
*/
bool Server::start()
{
    // 启动监听
    if (listen(sfd_, 5) < 0)
    {
        cerr << "listen  error" << endl;
        return false;
    }

    // 设置运行状态
    running_ = true; // 表示可以接收客户端请求了
    cout << "Server started on " << ip_ << ":" << port_ << endl;

    // 等待客户端的连接请求：循环完成
    while (running_)
    {
        sockaddr_in client_addr;                  // 接收客户端地址信息结构体
        socklen_t addr_len = sizeof(client_addr); // 接收客户端地址信息结构体的大小

        // 接收客户端连接请求操作
        int cfd = accept(sfd_, (struct sockaddr *)&client_addr, &addr_len);
        if (cfd < 0)
        {
            if (running_)
            {
                cerr << "accept error" << endl;
            }
            continue;
        }

        // 创建一个分支线程，在分支线程中，进行跟客户端的通信
        thread([this, cfd, client_addr]()
               {
            cout<<"Client connected :" << inet_ntoa(client_addr.sin_addr)<<":"<<ntohs(client_addr.sin_port)<<endl;

            //调用客户端处理函数
            handleClient(cfd, client_addr); })
            .detach(); // 将线程设置成分离态，资源由系统回收
    }

    return true;
}

/*
    停止服务器函数
    //关闭套接字文件描述符
*/
bool Server::stop()
{
    if (running_)
    {
        running_ = false; // 非运行
        close(sfd_);      // 关闭服务器套接字
        cout << "Server  stopped" << endl;
        return true;
    }
    return false;
}

/*
    处理客户端请求，分为不同的请求模式，接收客户端消息，根据不同类型进行不同的处理
    参数1：客户端套接字文件描述符
    参数2：客户端地址信息结构体
*/
void Server::handleClient(int cfd, sockaddr_in client_addr)
{
    Msg msg; // 用于存储收发的数据

    while (true)
    {
        // 接收客户端消息
        ssize_t recv_len = recv(cfd, &msg, sizeof(msg), 0);
        if (recv_len <= 0)
        {
            if (recv_len == 0) // 当前客户端已经下线
            {
                cout << "Client disconnect :" << inet_ntoa(client_addr.sin_addr) << endl;
            }
            else
            {
                cerr << "recv error" << endl;
            }
            break;
        }

        // 程序执行至此，表示正常读取到客户端的消息
        // 转换字节序
        msg.hostByteOrder();

        // 准备响应消息
        Msg response;                                            // 用于回复消息的容器
        strncpy(response.name, msg.name, sizeof(response.name)); // 表示要给谁传递消息
        response.type = msg.type;                                // 回复的消息类型

        // 根据不同的消息请求处理不同的响应
        switch (msg.type)
        {
        case R: // 注册
        {
            // 执行注册操作
            int success = db_manager_->registerUser(msg.name, msg.text);
            strcpy(response.text, success ? "**OK**" : "**EXISTS**"); // 如果成功注册回复OK，否则回复EXISTS
            break;
        }

        case L: // 登录
        {
            // 执行登录操作
            bool is_online = false;                                               // 返回是否已经在线
            bool success = db_manager_->loginUser(msg.name, msg.text, is_online); // 执行登录函数
            if (success)
            {
                strcpy(response.text, is_online ? "**EXISTS**" : "**OK**"); // 根据是否已经在线，进行回复
            }
            else
            {
                strcpy(response.text, "**FAIL**"); // 表示登录失败
            }
            break;
        }

        case Q: // 退出
        {
            // 执行退出操作
            db_manager_->logoutUser(msg.name);
            close(cfd);
            break;
        }

        case S: // 查询
        {
            // 执行查单词操作
            string meaning; // 报错单词含义
            if (db_manager_->querryWord(msg.text, meaning))
            {
                // 成功找到，将单词和含义一起回复给客户端
                snprintf(response.text, sizeof(response.text), "%s %s", msg.text, meaning.c_str());
            }
            else
            {
                strcpy(response.text, "Not Found"); // 表示没找到
            }

            // 保存查单词记录
            time_t now = time(NULL);                                          // 获取当前系统时间对应的秒数
            tm *local = localtime(&now);                                      // 将以秒数为单位的时间转变成时间的结构体
            char time_str[20] = "";                                           // 保存当前系统时间的字符串
            strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local); // 将结构体中的年月日时分秒转变成格式串

            // 调用历史查询记录
            db_manager_->recordHistory(msg.name, msg.text, meaning, time_str);

            break;
        }

        case H: // 历史记录
        {
            // 执行查看历史记录操作
            string history; // 保存得到的历史记录
            if (db_manager_->getHistory(msg.name, history))
            {
                // 表示执行成功，history中就有了历史记录
                strncpy(response.text, history.c_str(), sizeof(response.text)); // 将历史记录发送给客户端
            }
            else
            {
                strcpy(response.text, "No history"); // 当前用户没有进行查单词操作
            }
            break;
        }

        default:
            strcpy(response.text, "Ivalid Command"); // 表示请求非法
        }

        // 发送请求
        response.networkByteOrder(); // 转变成网络字节序
        if (send(cfd, &response, sizeof(response), 0) < 0)
        {
            cerr << "send error" << endl;
            break;
        }

        // 判断如果是查看历史记录，那么最后还要给出一个历史查询结束的情况
        if (msg.type == H)
        {
            strcpy(response.text, "**OVER**");
            send(cfd, &response, sizeof(response), 0);
        }
    }

    close(cfd); // 关闭客户端套接字
}

// 获取当前系统时间的静态成员函数
string Server::getCurrentTime()
{
    // 保存查单词记录
    time_t now = time(NULL);                                          // 获取当前系统时间对应的秒数
    tm *local = localtime(&now);                                      // 将以秒数为单位的时间转变成时间的结构体
    char time_str[20] = "";                                           // 保存当前系统时间的字符串
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local); // 将结构体中的年月日时分秒转变成格式串

    return string(time_str);
}