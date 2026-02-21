/*
This file contains the implementation of async using threads.

*/

#define _GNU_SOURCE
#include <sched.h>
//#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

int main() {
    unsigned num_cpus = std::thread::hardware_concurrency();
    std::cout<<"Num of cpus "<<num_cpus<<std::endl;
    
    std::vector<std::thread> threads(num_cpus);
    std::mutex mtx;                             // mutex for orderly access of shared resource or critical section

    for(int i=0;i<num_cpus;i++)
    {
        // capture by reference
        threads[i] = std::thread([&mtx, i](){
            {
            std::lock_guard<std::mutex> lock(mtx);
            // for windows
            // #ifdef _WIN32
            //  #include<windows.h>
            //  std::cout<<"Thread: " << i <<" is running on CPU: "<< GetCurrentProcessorNumber() <<std::endl;
            std::cout<<"Thread: " << i <<" is running on CPU: "<< sched_getcpu() <<std::endl;
            std::this_thread::sleep_for(std::chrono::microseconds(300));
            }
        });   
    }

    for (auto& t : threads){
        t.join();               // wait for thread to finish.
    } 
}

