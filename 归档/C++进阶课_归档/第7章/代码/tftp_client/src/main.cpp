#include "tftp_client.h"
#include <myhead.h>

int main(int argc, char const *argv[])
{
    // 对输入的服务器ip地址进行判断
    if (argc < 2)
    {
        cout << "请输入IP地址" << endl;
        return -1;
    }

    // 实例化对象
    try
    {
        TFTPClient client(argv[1]); // 通过有参构造，构造一个客户端
        client.run();               // 执行客户端
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    return 0;
}
