//C++ file
/***********************************************
#
#      Filename: threadTest.cpp
#
#        Author: luhg - luhengguang@gosuncn.com
#   Description: C++11 线程类的一些简单用法
#        Create: 2019-07-25 17:04:07
#**********************************************/
#include <iostream>
#include <thread>
#include <time.h>
#include <mutex>
//#include <chrono>

using namespace std;

mutex m;  // 线程互斥锁

class test {
        string name;
    public:
        test(string nn):name(nn) {}
        void hello() { 
            unique_lock<mutex> lock(m);  // 这种加锁方式无需手动解锁，对象会在析构的时候自动释放锁; 下面的加锁方式则要手动释放锁
            // m.lock();
            cout << "this is from class, thread name: " << this->name 
                 << ", threadID: " << this_thread::get_id() << endl; 
            // m.unlock();
        }
};


void hello(const char *sayHi) {
    unique_lock<mutex> lock(m);
    // m.lock();
    // 用get_id方法获取线程id
    cout << "this is from function, threadID: " << this_thread::get_id() 
         << ", Welcome " << sayHi << endl;
    // m.unlock();
}


int main() {
    test tt1("111");
    thread t1(&test::hello, &tt1);  // 向thread中传递类成员函数的方法
    thread t2(hello, "Edward");  // 向thread中传递普通函数的方法，第二个参数及之后的是传入函数的参数

    /*
     * cout << t1.get_id() << endl;  // 获取线程ID的方法
     */
    t1.join();
    t2.join();

    // 线程休眠
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "main here" << endl;

    return 0;
}

int main1()
{
    // 获取主线程的id
    thread::id id = this_thread::get_id();
    cout << hash<thread::id>()(id) << endl;
    cout << "cout ----- id : " << id << endl;
    return 0;
}
