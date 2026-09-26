#include <myhead.h>
#include<thread>

void TestThread()
{
    cout<<"=========================================="<<endl;
    cout<<"test 001"<<endl;
    cout<<"test 002"<<endl;
    cout<<"test 003"<<endl;
    cout<<"=========================================="<<endl;
}



/***************主程序********************/
int main(int argc, const char *argv[]) 
{
    for(int i=0; i<100000; i++)
    {
        thread th(TestThread);

        th.detach();
        
    }

    this_thread::sleep_for(chrono::seconds(5));


    std::cout << "Hello, World!" << std::endl;
   return 0;
}