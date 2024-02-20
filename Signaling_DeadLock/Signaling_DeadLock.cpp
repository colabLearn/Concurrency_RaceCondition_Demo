#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
int counter1 = 0;
int counter2 = 0;
int result1 = 0;
int result2 = 0;
mutex mutex1, mutex2;
condition_variable cv;
int c1 = 0;
int c2 = 0;
void incrementCounter1() {
    
    for (int i = 0; i < 10; ++i) {
        unique_lock<mutex> lock1(mutex1);
        counter1++;
       
        cout << "Thread 1 acquire counter1 resources successfully" << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        
        unique_lock<mutex> lock2(mutex2, defer_lock);
        if (lock2.try_lock())
        {
           
            cout << "Thread 1 acquire counter2 resources successfully" << endl;
            this_thread::sleep_for(chrono::milliseconds(100));
            counter2++;
            counter1++;
            lock2.unlock();
            lock1.unlock();
            cv.notify_one();
           
        }
        else
        {    
            lock1.unlock();
            lock2.lock();
            cv.wait(lock2, [] {return true; });
           
        }
        
    }
    
}
void incrementCounter2() {
    
    for (int i = 0; i < 10; ++i) {

        unique_lock<mutex> lock2(mutex2);
        counter2++;
        cout << "Thread 2 acquire counter2 resources successfully" << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        
        unique_lock<mutex> lock1(mutex1, defer_lock);
        if (lock1.try_lock())
        {
           
            this_thread::sleep_for(chrono::milliseconds(100));
            cout << "Thread 2 acquire counter1 resources successfully" << endl;
            counter1++;
            counter2++;
            lock1.unlock();
            lock2.unlock();
            cv.notify_one();

          
        }
        else
        {
           
            lock2.unlock();
            lock1.lock();
            cv.wait(lock1, [] {return true; });
        }
        

    }
    
}
int main()
{
    thread t1(incrementCounter1);
    thread t2(incrementCounter2);

    t1.join();
    t2.join();
    //incrementCounter1();
    //incrementCounter2();

    cout << "Final counter 1 value is: " << counter1 << endl;
    cout << "Final counter 2 value is: " << counter2 << endl;
}

