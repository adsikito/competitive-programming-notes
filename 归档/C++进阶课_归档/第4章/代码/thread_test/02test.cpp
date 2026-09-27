#include <myhead.h>

#include<thread>

void ThreadMain(int p1, double p2, string str)
{
    cout<<"thread::" <<p1<< " "<< p2<< "   "<<str<<endl;
    
}




int main(int argc, const char *argv[]) 
{

    cout << "main thread ID:" << this_thread::get_id() <<endl;

    //线程创建启动
    thread th(ThreadMain, 520, 3.14, "hello world");



    //阻塞等待子线程退出
    th.join();



    std::cout << "Hello, World!" << std::endl;
    return 0;
}