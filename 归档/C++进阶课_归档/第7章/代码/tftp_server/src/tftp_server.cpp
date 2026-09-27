#include "tftp_server.h"

// 用户打印错误信息的宏
#define ERR_LOG(msg)                                                      \
    do                                                                    \
    {                                                                     \
        perror(msg);                                                      \
        cout << __LINE__ << "  " << __func__ << "  " << __FILE__ << endl; \
    } while (0)

// 构造函数的定义
TFTPServer::TFTPServer(const string &root) : root_dir(root)
{
    // 创建UDP套接字
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd < 0)
    {
        ERR_LOG("socker error");
        return;
    }

    // 填充地址信息结构体
    server_addr.sin_family = AF_INET;                // 通信域
    server_addr.sin_port = htons(PORT);              // 端口号
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 表示任意一个主机都可以向我发消息

    // 设置端口号快速重用
    int reuse = 1;
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
    {
        ERR_LOG("setsockopt error");
        return;
    }

    // 绑定工作
    if (bind(sfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        ERR_LOG("bind error");
        return;
    }
}

// 析构函数的定义
TFTPServer::~TFTPServer()
{
    if (sfd >= 0)
    {
        close(sfd);
    }
}

// 定义运行函数
void TFTPServer::run()
{
    // 给出提示消息
    cout << "TFTP Server started on port:" << PORT << endl;
    cout << "Serving  file from:" << root_dir << endl;

    char buf[BUFFER_SIZE] = "";               // 用来存储数据包
    struct sockaddr_in client_addr;           // 用来存储客户端地址信息结构体
    socklen_t addr_len = sizeof(client_addr); // 存储客户端地址信息结构体的大小

    // 循环跑服务器
    while (true)
    {
        // 接收客户端的请求包
        int n = recvfrom(sfd, buf, BUFFER_SIZE, 0,
                         (struct sockaddr *)&client_addr, &addr_len);
        if (n < 0)
        {
            ERR_LOG("recvfrom error");
            return;
        }

        // 检查操作码
        if (buf[0] != 0)
            continue; // 说明协议错误

        // 解析请求包
        char *filename = buf + 2;                           // 解析请求文件名
        const char *mode = filename + strlen(filename) + 1; // 得到协议模式

        // 检查传输格式
        if (strcasecmp(mode, "octet") != 0)
        {
            sendError("Only binary mode supportd", client_addr);
            continue;
        }

        // 处理正常请求
        switch (buf[1])
        {
        case 1: // 读请求
            cout << "read request for :" << filename << endl;
            // 调用处理读请求的函数
            handleReadRequest(filename, client_addr, addr_len);
            break;

        case 2: // 写请求
            cout << "write request for :" << filename << endl;
            // 调用处理读请求的函数
            handleWriteRequest(filename, client_addr, addr_len);
            break;
        default:
            sendError("Unknown request", client_addr); // 处理异常请求
            break;
        }
    }
}

// 处理读请求的函数实现
void TFTPServer::handleReadRequest(const char *filename, struct sockaddr_in &client_addr,
                                   socklen_t addr_len)
{
    // 找到要下载的文件路径
    string full_path = root_dir + "/" + filename; // C++中字符串可以是+拼接
    // 以只读的形式打开文件
    int fd = open(full_path.c_str(), O_RDONLY);
    if (fd < 0)
    {
        // 表示要下载的文件再服务器中不存在
        sendError("File not found", client_addr);
        return;
    }

    // c程序执行至此，表示要下载的文件在服务器中存在
    char buf[BUFFER_SIZE] = "";   // 数据包
    unsigned short block_num = 1; // 块编号

    // 循环发送数据包
    while (true)
    {
        // 准备数据包
        buf[0] = 0;
        buf[1] = 3;                                      // 表示数据包
        *(unsigned short *)(buf + 2) = htons(block_num); // 块编号封装到数据包中

        // 从文件中读取数据到 buf +4之后
        int n = read(fd, buf + 4, BUFFER_SIZE - 4);
        if (n < 0)
        {
            sendError("Read error", client_addr);
            close(fd);
            return;
        }

        // 程序执行至此，表示数据包已经封装好，将数据包发送给客户端
        if (sendto(sfd, buf, n + 4, 0, (struct sockaddr *)&client_addr, addr_len) < 0)
        {
            ERR_LOG("sendto error");
            close(fd);
            return;
        }

        // 程序执行至此，表示服务器成功将一个数据包发送给了客户端
        // 等待客户端反馈ACK
        do
        {
            // 收取客户端发来的ACK数据包
            if (recvfrom(sfd, buf, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len) < 0)
            {
                ERR_LOG("recvfrom error");
                close(fd);
                return;
            }
        } while (buf[1] != 4 || ntohs(*(unsigned short *)(buf + 2)) != block_num);

        // 判断当前的文件是否读取结束
        if (n < BUFFER_SIZE - 4)
        {
            break;
        }

        // 程序执行至此，表示还有数据等待发送，此时块编号应该自增
        block_num++;
    }

    // 关闭文件描述符
    close(fd);
}

// 处理写请求的函数实现
void TFTPServer::handleWriteRequest(const char *filename, struct sockaddr_in &client_addr,
                                    socklen_t addr_len)
{
    // 找到要上传的文件路径
    string full_path = root_dir + "/" + filename; // C++中字符串可以是+拼接
    // 以只写的形式打开文件
    int fd = open(full_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd < 0)
    {
        // 表示创建文件失败
        sendError("Cannot create file", client_addr);
        return;
    }

    // 程序执行至此，表示已经创建好文件
    // 发送ACK
    char buf[BUFFER_SIZE] = "";   // 数据包
    unsigned short block_num = 0; // 块编号

    buf[0] = 0;
    buf[1] = 4;                                      // ACK包
    *(unsigned short *)(buf + 2) = htons(block_num); // 块编号

    // 发送ACK
    if (sendto(sfd, buf, 4, 0, (struct sockaddr *)&client_addr, addr_len) < 0)
    {
        ERR_LOG("sendto error");
        return;
    }

    // 循环接收数据包
    while (true)
    {
        // 读取数据包
        int n = recvfrom(sfd, buf, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (n < 0)
        {
            ERR_LOG("recvfrom error");
            close(fd);
            return;
        }

        // 判断是否为数据包
        if (buf[1] == 3 && ntohs(*(unsigned short *)(buf + 2)) == block_num + 1)
        {
            // 说明是数据包，将数据包中的数据，写入到文件中
            if (write(fd, buf + 4, n - 4) < 0)
            {
                sendError("Write error", client_addr);
                close(fd);
                return;
            }

            // 向客户端发送一个ACK
            block_num++;
            buf[0] = 0;
            buf[1] = 4;                                      // 说明是ACK包
            *(unsigned short *)(buf + 2) = htons(block_num); // 块编号
            if (sendto(sfd, buf, 4, 0, (struct sockaddr *)&client_addr, addr_len) < 0)
            {
                ERR_LOG("sendto error");
                return;
            }

            // 判断读取的数据的长度跟缓冲区长度大小
            if (n < BUFFER_SIZE)
            {
                break; // 表示上传完成
            }
        }
    }

    close(fd); // 关闭文件
}

// 发送错误信息
void TFTPServer::sendError(const char *msg, struct sockaddr_in &client_addr)
{
    // 封装错误包
    char buf[BUFFER_SIZE] = "";

    buf[0] = 0;
    buf[1] = 5; // 错误包的操作码
    buf[2] = 0;
    buf[3] = 1;           // 错误码
    strcpy(buf + 4, msg); // 错误信息

    // 将消息发送给客户端
    if (sendto(sfd, buf, strlen(msg) + 5, 0, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0)
    {
        ERR_LOG("sendto error");
        return;
    }
}
