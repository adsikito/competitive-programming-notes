#include <myhead.h>
#include "http.h"

// 定义线程体函数
void *msg_request(void *arg)
{
    // 解析到传进来的客户端的套接字文件描述符
    int sock = *(int *)arg;
    delete (int *)arg;
    // 调用信息处理函数，该函数是所有请求的入口
    handler_msg(sock);
    close(sock);
    return NULL;
}

/*******************主程序**************************** */
int main(int argc, const char *argv[])
{
    int port = 80; // 默认使用80端口号

    // 判断是否手动传入端口号
    if (argc > 1)
    {
        port = atoi(argv[1]);
        // atoi：功能：将给定的字符串转变成整数
        // 参数：字符串（只能包含数字字符）
        // 返回值：整数      例如：“123”  ---> 123
    }

    // 初始化服务器
    // 自定义函数：功能完成tcp服务器的初始化操作 创建套接字、绑定端口号、监听
    // 参数：端口号
    // 返回值：服务器套接字
    int lis_socket = init_server(port);

    // 循环接收客户端的连接请求
    // 并发服务器使用多线程完成
    while (1)
    {
        struct sockaddr_in peer;      // 接收客户端的地址信息结构体
        socklen_t len = sizeof(peer); // 接收长度

        // 接收客户端的连接请求
        // 返回的套接字就是服务器端创建处理的用于跟客户端进行通信的套接字文件描述符
        int sock = accept(lis_socket, (struct sockaddr *)&peer, &len);
        if (sock == -1)
        {
            perror("accept error");
            return -1;
        }

        printf("您有新的客户端(%d)发来连接请求了\n", sock);

        // 创建一个分支线程用户跟客户端进行通信
        pthread_t tid = -1;
        if (pthread_create(&tid, NULL, msg_request, new int(sock)) > 0)
        {
            printf("pthread_create error\n");
            return -1;
        }

        // 将线程设置成分离态
        pthread_detach(tid);
    }

    // 关闭服务器
    close(lis_socket);
    return 0;
}