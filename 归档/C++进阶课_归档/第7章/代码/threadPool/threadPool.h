#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>             //用于存储多个线程
#include <thread>             //线程的创建及管理
#include <queue>              //用于存储多个任务的队列
#include <condition_variable> //条件变量头文件
#include <mutex>              //互斥锁头文件
#include <functional>         //用于使用函数类型
#include <myhead.h>           //自定义的头文件

class threadPool
{
private:
    // 线程池相关的私有成员
    vector<thread> workers;        // 存储工作的线程容器
    queue<function<void()>> tasks; // 存储任务的队列
    mutex task_mutex;              // 互斥锁
    condition_variable task_cv;    // 用于通知线程有新任务的条件变量
    bool stop;                     // 线程池的标志，判断线程池是否停止

    // 启动线程池
    void startThreadPool(size_t numThreads);

public:
    threadPool(int threadPoolSize); // 构造函数声明
    ~threadPool();                  // 析构函数声明

    void addTask(function<void()> task); // 添加任务到线程池
};

#endif