#include <myhead.h>
#include "threadPool.h"

int main(int argc, const char *argv[])
{
    threadPool mypool(3); // 一个线程池初始化4个线程

    for (int i = 0; i < 20; i++) // 添加20个任务到线程池
    {
        mypool.addTask([i]()
                       {
            //使用lambda表达式当做线程体函数

            cout<<"任务："<<i<<"正在执行，其tid = "<<this_thread::get_id()<<endl;

            //模拟任务执行时间，表示该任务执行100毫秒
            this_thread::sleep_for(std::chrono::milliseconds(500)); });
    }

    // 等待所有任务完成
    this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}