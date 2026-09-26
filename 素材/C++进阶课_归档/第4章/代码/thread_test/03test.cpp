#include <myhead.h>

#include<thread>

class MyThread
{
    public:
        void Main()
        {
            cout<<"MyYhread Main "<<name<<":"<<age<<endl;
        }

        string name;
        int age;

};




int main(int argc, const char *argv[]) 
{

    MyThread myth;
    myth.name = "zpp";
    myth.age = 18;

    thread th(&MyThread::Main, &myth);



    //阻塞等待子线程退出
    th.join();



    std::cout << "Hello, World!" << std::endl;
    return 0;
}