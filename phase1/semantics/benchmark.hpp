
#include<chrono>
#include<iostream>

class StopWatch {
    //std::chrono::milliseconds

    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
    
    public:

    StopWatch() {
        std::cout<<"StopWatch Start"<<std::endl;
        start = std::chrono::steady_clock::now();
    }

    ~StopWatch() {

    }

    void print_duration(){
        end = std::chrono::steady_clock::now();
        std::cout<<"StopWatch End"<<std::endl;

        std::cout<<"Duration to finish compute: "<<std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()<<" milli sec"<<std::endl;
    }

};