#include "threadPool.h"

// 构造函数定义
threadPool::threadPool(int threadPoolSize) : stop(false)
{
    startThreadPool(threadPoolSize); // 启动线程池
}

// 析构函数的定义
threadPool::~threadPool()
{
    {
        unique_lock<mutex> lock(task_mutex); // 获取锁资源，用于保护stop变量
        stop = true;
    }

    // 将所有的等待线程唤醒
    task_cv.notify_all();

    // 将所有的工作线程回收
    for (auto &worker : workers)
    {
        worker.join();
    }
}

// 将任务加到线程池中
void threadPool::addTask(function<void()> task)
{
    {
        unique_lock<mutex> lock(task_mutex); // 获取锁资源，保护条件变量
        tasks.push(task);                    // 将任务添加到任务队列
    }

    // 唤醒一个等待的线程开始工作
    task_cv.notify_one(); // 唤醒一个线程去工作
}

// 启动线程池函数的定义
void threadPool::startThreadPool(size_t numThreads)
{
    // 循环创建numThreads个线程
    for (int i = 0; i < numThreads; i++)
    {
        // 创建一个线程，并且将线程放入到线程容器中
        workers.emplace_back([this] // 使用lambda表达式定义线程体
                             {
            while(true)
            {
                function<void()> task;    //创建一个任务
                {
                    unique_lock<mutex> lock(task_mutex);     //加锁，保护任务队列
                    task_cv.wait(lock, [this]{       //等待条件变量通知
                        return stop || !tasks.empty(); //当线程池停止工作或者任务队列不为空时
                    });

                    if(stop && tasks.empty())
                    {
                        return;              //当线程池停止或者任务队列为空，退出线程
                    }

                    task = move(tasks.front());     //从任务队列中取出一个任务
                    tasks.pop();                   //将任务从任务队列中移除 
                }
                task();           //执行任务
            } });
    }
}
