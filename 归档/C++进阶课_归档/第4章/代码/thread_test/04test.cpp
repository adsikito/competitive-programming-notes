#include <myhead.h>

#include<thread>



int main(int argc, const char *argv[]) 
{

    thread th([](int i){
        cout << "test lambda :"<<i<<endl;
    }, 520);

    th.join();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}