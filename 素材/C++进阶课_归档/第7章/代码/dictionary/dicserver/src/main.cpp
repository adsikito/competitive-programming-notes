#include "database_manager.hpp"
#include "server.hpp" //服务器的头文件

#include <myhead.h>

int main(int argc, const char *argv[])
{

    // 判断外部是否传入的三个参数
    if (argc != 3)
    {
        cerr << "用法：" << argv[0] << "<IP> <port>" << endl;
        return -1;
    }

    try
    {
        // 构造一个数据库管理对象，用于管理两个数据库
        auto db_manager = make_shared<DatabaseManager>("usr.db", "dict.db");
        // 初始化数据库
        if (!db_manager->initalizeDatabase())
        {
            cerr << "数据库初始化失败，请检查：" << endl;
            cerr << "1、dict.txt文件是否存在" << endl;
            cerr << "2、当前目录是否具有写权限" << endl;
            return -1;
        }

        // 构造一个服务器
        Server server(db_manager, argv[1], atoi(argv[2]));
        // 启动服务器
        server.start();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << endl;
        return -1;
    }
    return 0;
}