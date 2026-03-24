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

#if defined(__APPLE__)
    #include <mach/mach.h>
    #include <mach/thread_info.h>
#endif



int get_cpu_number()
{
    #if defined(__linux__)
        #define _GNU_SOURCE
        #include <sched.h>
        return sched_getcpu();

    #elif defined(_WIN32)
        #include <windows.h>
        return GetCurrentProcessorNumber();

    #elif defined(__APPLE__)
        thread_identifier_info_data_t t_id;
        mach_msg_type_number_t count = THREAD_IDENTIFIER_INFO_COUNT;

        if (thread_info(mach_thread_self(), THREAD_IDENTIFIER_INFO, (thread_info_t)&t_id, &count) != KERN_SUCCESS) 
        {
            return -1;
        }

        return (int)t_id.thread_id;
    #else
        return -1;
    #endif
}

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
            std::cout<<"Thread: " << i <<" is running on CPU: "<< get_cpu_number() <<std::endl;
            std::this_thread::sleep_for(std::chrono::microseconds(300));
        }});
    }

    for (auto& t : threads){
        t.join();               // wait for thread to finish.
    } 
}

