#include <myhead.h>

#include<thread>

void ThreadMain()
{
    cout<<"begin thread main" << endl;
    cout << "child thread ID:" << this_thread::get_id() <<endl;
    for (int i = 0; i < 10; i++)
    {
        cout<<"in thread :" <<i<<endl;
        this_thread::sleep_for(chrono::seconds(1));      //1000毫秒
    }
    
}




int main(int argc, const char *argv[]) 
{

    cout << "main thread ID:" << this_thread::get_id() <<endl;

    //线程创建启动
    thread th(ThreadMain);



    //阻塞等待子线程退出
    th.join();



    std::cout << "Hello, World!" << std::endl;
    return 0;
}