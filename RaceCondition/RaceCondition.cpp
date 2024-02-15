//Race condition Demo
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int counter = 0;
mutex counterMutex;

void incrementCounter()
{
   
    for (int i = 0; i < 100000; ++i)
    {
        counter++;
    }
}


// Function to increment the counter
void incrementCounter2() {
    for (int i = 0; i < 100000; ++i) {

        //synchronization with counterMutex
        counterMutex.lock();
        counter++;
        counterMutex.unlock();
    }
}

int main()
{
    //The two threads needs to increament the counter concurrently
    thread t1(incrementCounter2);
    thread t2(incrementCounter2);

    //This functoin helps to add some delay in thread t3
    //Althugh it does the same thing with incrementCounter2
    //thread t3([]() 
      //  {
      //  for (int i = 0; i < 100000; ++i) {
      //      counterMutex.lock();
      //      counter++;
      //      counterMutex.unlock();
      //  }
      //  });


    t1.join();
    t2.join();
   // t3.join();
    
    cout<< "Counter value: " << counter << endl;
}

