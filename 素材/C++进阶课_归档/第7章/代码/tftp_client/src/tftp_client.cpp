#include "tftp_client.h"

// 用户打印错误信息的宏
#define ERR_LOG(msg)                                                      \
    do                                                                    \
    {                                                                     \
        perror(msg);                                                      \
        cout << __LINE__ << "  " << __func__ << "  " << __FILE__ << endl; \
    } while (0)

// 构造函数的定义
TFTPClient::TFTPClient(const string &serverIP)
{
    // 创建udp套接字
    this->sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd < 0)
    {
        ERR_LOG("sock error");
        return;
    }

    // 设置服务器地址信息结构体
    server_addr.sin_family = AF_INET;                          // 通信域
    server_addr.sin_port = htons(PORT);                        // 服务器端口号
    server_addr.sin_addr.s_addr = inet_addr(serverIP.c_str()); // 服务器ip地址
}

// 析构函数的定义
TFTPClient::~TFTPClient()
{
    if (sfd > 0)
    {
        close(sfd); // 如果套接字没有被关闭，则关闭套接字
    }
}

// 定义运行函数
void TFTPClient::run()
{
    while (true)
    {
        // 展示菜单
        showMenu();

        char choice;    // 菜单选项
        cin >> choice;  // 输入选项
        waitForInput(); // 吸收垃圾字符

        switch (choice)
        {
        case '1':
            doDownload(); // 执行下载请求
            break;

        case '2':
            doUpload(); // 执行下载请求
            break;

        case '3':
            return;

        default:
            cout << "您输入的功能有误，请重新输入" << endl;
            break;
        }

        clearScream(); // 清屏
    }
}

// 下载函数的定义
int TFTPClient::doDownload()
{
    string filename; // 存储要下载的文件名
    cout << "请输入要下载的文件文件名称：";
    // cin >> filename;               //这种只能输入没有空格的字符串 不建议使用
    std::getline(cin, filename); // 既可以输入无空格的字符串，也可以输入有空格的字符串

    // 封装下载请求
    char buf[BUFFER_SIZE] = "";
    int size = sprintf(buf, "%c%c%s%c%s%c", 0, 1, filename.c_str(), 0, "octet", 0); // 封装请求包
    // 向服务器发送请求
    if (sendto(sfd, buf, size, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        ERR_LOG("sendto error");
        return -1;
    }

    // 循环接收服务器发来的数据包
    size_t recv_len;
    unsigned short num = 1;                  // 记录接收的数据块编号
    socklen_t addrlen = sizeof(server_addr); // 接收服务器地址信息结构体的大小

    // 定义有关文件操作的遍历
    int flag = 0; // 标识文件是否被打开
    int fd;       // 文件描述符

    // 启动循环
    while (true)
    {
        // 清空消息容器
        bzero(buf, BUFFER_SIZE);

        // 读取服务器发来的消息
        recv_len = recvfrom(sfd, buf, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addrlen);
        if (recv_len < 0)
        {
            ERR_LOG("recvfrom error");
            return -1;
        }

        // 对读取下来的数据进行分析
        // 判断是否为数据包
        if (3 == buf[1])
        {
            // 读取数据操作
            // 打开文件操作
            if (0 == flag) // 表示文件没有被打开
            {
                fd = open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0664);
                if (fd < 0)
                {
                    ERR_LOG("open error");
                    return -1;
                }
                // 更改标识位
                flag = 1; // 表示文件已经打开
            }

            // 判断数据
            if (htons(num) == *(unsigned short *)(buf + 2)) // 表示是传过来的数据包
            {
                // 将数据包中的数据写入文件
                if (write(fd, buf + 4, recv_len - 4) < 0)
                {
                    cout << "fd = " << fd << "   recv_len = " << recv_len << endl;
                    ERR_LOG("write error");
                    close(fd);
                    break;
                }
            }

            // 组装ACK包，发送给服务器
            buf[1] = 4; // ACK
            if (sendto(sfd, buf, 4, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
            {
                ERR_LOG("sendto error");
                close(fd);
                return -1;
            }

            // 判断收取的数据长度是否小于容器长度
            if (recv_len < BUFFER_SIZE) // 表示该数据包是最后一个数据包了
            {
                cout << "--------文件下载完毕-----------" << endl;
                close(fd);
                break;
            }

            num++; // 块编号自增
        }
        else if (5 == buf[1])
        {
            // 说明有错误信息
            cout << "______error: " << (buf + 4) << "________" << endl;
            if (flag == 1) // 出现错误时，文件也需要关闭
            {
                close(fd);
            }
            break;
        }
    }
}
// 上传函数的定义
int TFTPClient::doUpload()
{
    string filename; // 存储要上传的文件名
    cout << "请输入要上传的文件名：";
    getline(cin, filename);

    // 检查文件是否存在
    int fd = open(filename.c_str(), O_RDONLY); // 以只读的形式打开文件，如果文件不存在，则报错
    if (fd < 0)
    {
        if (errno == ENOENT)
        {
            cout << "文件不存在" << endl;
            return -2;
        }
        ERR_LOG("open error");
        return -1;
    }

    // 程序执行至此，表示文件存在

    // 构造上传请求
    char buf[BUFFER_SIZE] = "";
    int size = sprintf(buf, "%c%c%s%c%s%c", 0, 2, filename.c_str(), 0, "octet", 0);

    if (sendto(sfd, buf, size, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        ERR_LOG("sendto error");
        close(fd);
        return -1;
    }

    // 循环接收服务器发来的消息
    int recv_len;           // 接收的消息长度
    unsigned short num = 0; // 消息块
    socklen_t addrlen = sizeof(server_addr);

    while (true)
    {
        // 清空容器
        bzero(buf, BUFFER_SIZE);
        // 读取服务器发来的消息
        recv_len = recvfrom(sfd, buf, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addrlen);
        if (recv_len < 0)
        {
            ERR_LOG("recvfrom error");
            close(fd);
            return -1;
        }

        // 判断消息类型
        if (4 == buf[1])
        {
            // 表示收到的是服务器发来的ACK包
            // 判断块编号
            if (num == ntohs(*(unsigned short *)(buf + 2)))
            {
                buf[1] = 3;                                // 修改为数据包
                num++;                                     // 块编号自增
                *(unsigned short *)(buf + 2) = htons(num); // 修改块编号
            }

            // 组装下一个数据包
            // 从文件中读取数据
            int res = read(fd, buf + 4, BUFFER_SIZE - 4);
            if (res < 0) // 说明读取失败
            {
                ERR_LOG("read error");
                close(fd);
                break;
            }
            else if (res == 0) // 说明文件读完了
            {
                cout << "------------上传完毕-------------" << endl;
                break;
            }

            // 向服务器发送数据包
            if (sendto(sfd, buf, res + 4, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
            {
                ERR_LOG("sendto error");
                close(fd);
                return -1;
            }
        }
        else if (5 == buf[1])
        {
            // 表示服务器发来的是错误包
            cout << "------------文件上传失败，请检查网络-------------" << endl;
            break;
        }
    }
}
// 清屏函数的定义
void TFTPClient::clearScream()
{
    cout << "请输入任意字符进行清屏";
    while (getchar() != '\n')
        ;
}
// 吸收垃圾字符的函数的定义
void TFTPClient::waitForInput()
{
    while (getchar() != '\n')
        ;
}
// 菜单函数的定义
void TFTPClient::showMenu()
{
    // 清屏
    system("clear");
    cout << "******************基于UDP的TFTP文件传输********************" << endl;
    cout << "*********************1、下载************************" << endl;
    cout << "*********************2、上传************************" << endl;
    cout << "*********************3、退出************************" << endl;
    cout << "**********************************************************" << endl;
}