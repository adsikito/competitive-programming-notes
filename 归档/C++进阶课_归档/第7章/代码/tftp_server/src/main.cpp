#include <myhead.h>
#include "tftp_server.h" //自定义类的头文件

int main(int argc, const char *argv[])
{

    try
    {
        string root_dir = (argc > 1) ? argv[1] : "."; // 如果外部传入的要操作的文件路径，则使用操作的路径
                                                      // 否则使用可执行程序所在的路径作为要操作的路径
        // 构造一个服务器
        TFTPServer server(root_dir);

        // 运行服务器
        server.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    return 0;
}