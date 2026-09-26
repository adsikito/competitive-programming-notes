#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <myhead.h>

// 操作类型的定义
#define R 1 // 用户注册
#define L 2 // 用户登录
#define Q 3 // 用户退出
#define S 4 // 单词查询
#define H 5 // 历史记录

// 定义客户端与服务器进行数据通信的协议
struct Msg
{
    int type;       // 操作类型
    char name[20];  // 用户名
    char text[128]; // 文本内容  （密码/单词）

    // 定义相关字节序的转换函数
    // 主机字节序转网络字节序
    void networkByteOrder()
    {
        type = htonl(type);
    }

    // 网络字节序转主机字节序
    void hostByteOrder()
    {
        type = ntohl(type);
    }
};

#endif