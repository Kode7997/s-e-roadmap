#include<iostream>
#include<memory>
#include<atomic>
#include<thread>

#include "../semantics/benchmark.hpp"

struct BadCacheLineData {
    std::atomic<int> cnt1 = 0;
    
    //adding padding to avoid false sharing or another method is to use alignas(64) to align the data to cache line size.
    //char padding[64 - sizeof(std::atomic<int>)];
    std::atomic<int> cnt2 = 0;
};

/*
// In C++17 and later: This helps to avoid false sharing by aligning each counter to a separate cache line, ensuring that 
// updates to one counter do not cause cache invalidation for the other.
struct ModernCounters {
    alignas(std::hardware_destructive_interference_size) 
    std::atomic<int> counter1;
    
    alignas(std::hardware_destructive_interference_size)
    std::atomic<int> counter2;
};
*/


typedef struct BadCacheLineData bcl;

int main() {
    std::cout<<"size: "<<sizeof(BadCacheLineData)<<std::endl;
    size_t n = 10000000;

    bcl data;
    StopWatch sw;

    std::thread t1([&data, n, &sw](){
        sw.start_timer();
        for(size_t i=0;i<n;i++){
            //std::cout<<"cnt1: "<<data.cnt1<<std::endl;
            data.cnt1++;
            data.cnt2++;
        }
        sw.print_duration();
    });
    


    StopWatch sw1;
    std::thread t2([&data, n, &sw1](){
        sw1.start_timer();
        for(size_t i=0;i<n;i++){
            //std::cout<<"cnt2: "<<data.cnt2<<std::endl;
            data.cnt2++;
        }
        sw1.print_duration();
    });
    

    t1.join();
    t2.join();
}