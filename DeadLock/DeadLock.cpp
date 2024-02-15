

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
int counter1 = 0;
int counter2 = 0;
int result1 = 0;
int result2 = 0;
mutex mutex1, mutex2;
void incrementCounter1() {
    for (int i = 0; i < 100000; ++i) {

        
        mutex1.lock();
        counter1++;
        cout << "Thread 1 acquire counter1 resources successfully" << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        //mutex1.unlock();
        mutex2.lock();
        counter2++;
        cout << "Thread 1 acquire counter2 resources successfully" << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        result1 = counter1 + counter2;
        mutex1.unlock();
        mutex2.unlock();


    }
}
void incrementCounter2() {
    for (int i = 0; i < 100000; ++i) {

        //synchronization with counterMutex
        mutex2.lock();
        counter2++;
        cout << "Thread 2 acquire counter2 resources successfully" << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        //mutex2.unlock();
        mutex1.lock();
        counter1++;
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Thread 1 acquire counter1 resources successfully" << endl;
        result2 = counter1 + counter2;
        mutex2.unlock();
        mutex1.unlock();

    }
}
int main()
{
    thread t1(incrementCounter1);
    thread t2(incrementCounter2);

    t1.join();
    t2.join();

}

