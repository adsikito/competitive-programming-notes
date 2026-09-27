#include <myhead.h>
#include <thread>
#include <list>
#include <sstream>
#include <mutex>
#include <condition_variable>
list<string> msgs_; // 字符串链表
mutex mux;
condition_variable cv;

void ThreadWrite()
{
    for (int i = 0;; i++)
    {
        stringstream ss;
        ss << "Write msg " << i;

        unique_lock<mutex> lock(mux);
        msgs_.push_back(ss.str());
        mux.unlock();

        cv.notify_one();            //唤醒一个线程

        this_thread::sleep_for(1s);
    }
}

void ThreadRead(int i)
{
    for (;;)
    {


        cout << "read msg" << endl;

        unique_lock<mutex> lock(mux);
        cv.wait(lock);

        if (msgs_.empty())
            return;

        while (!msgs_.empty())
        {
            cout << i << " read " << msgs_.front() << endl;
            msgs_.pop_front();
        }
    }
}

int main(int argc, const char *argv[])
{
    thread th(ThreadWrite);
    th.detach();

    for (int i = 0; i < 3; i++)
    {
        thread th(ThreadRead, i + 1);
        th.detach();
    }

    getchar();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}