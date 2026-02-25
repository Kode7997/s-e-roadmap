
/*
Thread - for parallel computation. assign work to each of the thread
mutex - it is used for orderly access of resource or critical section
locks - used to lock specific section of code to achieve mutual exclusive.
async - Tasks based parallelism. chunks of works. async is an api to launch
        these tasks and make sure work is load-balanced. 
atomic - lock-free mechanism.

Policies of Async:
    1. std::launch::async -- creates new thread and executes when async is created
    2. std::launch::deferred -- execute when get() or wait() called and does NOT create New thread.
    3. async -- OS wil decide 
*/

#include <iostream>
#include <chrono>
#include <future>
#include <thread>

int some_expensive_compute(int number)
{
    std::cout<<"Start of expensive computation"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout<<"End of expensive compuatation"<<std::endl;

    return number * number;
}

int main()
{
    std::cout<<"Demonstrate async calls"<<std::endl;
    
    auto future = std::async(std::launch::async, some_expensive_compute, 10);

    std::cout<<"Thread created to start some expensive computation"<<std::endl;
    std::cout<<"Main thread continue to do its job..."<<std::endl;

    //get the result of expensive computation
    /*
    Two scenarios:
    1. Result ready - if result is ready then future.get return value/result
    2. Result Not ready - It blocks further computation until it gets the result.
    */

    int result = future.get();
    std::cout<<"Result: "<<result<<std::endl;

}
