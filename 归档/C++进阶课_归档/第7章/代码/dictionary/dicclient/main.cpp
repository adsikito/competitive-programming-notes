#include "client.hpp"

#include <myhead.h>

int main(int argc, const char *argv[])
{
    // 判断传入的数据是否足够
    if (argc != 3)
    {
        cerr << "用法：" << argv[0] << " <服务器ip> <端口号>" << endl;
        return -1;
    }

    // 实例化客户端对象
    try
    {
        DictClient client(argv[1], atoi(argv[2])); // 实例化客户端对象
        client.run();                              // 运行主要逻辑
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}