
#include <iostream>
#include <vector>
#include "../semantics/benchmark.hpp"

class CPY_MOV {
    public:

    std::vector<int> vec;

    CPY_MOV():vec(0) {
        std::cout<<"CTOR CPY_MOV"<<std::endl;
        std::cout<<"Vector size: "<<vec.size()<<std::endl;
    }

    // copy constructor, copy each element if not empty to current class object
    CPY_MOV(const CPY_MOV& other) {
        std::cout<<"CTOR COPY"<<std::endl;

        if(other.vec.size() == 0){
            return;
        }

        for(int i =0; i< other.vec.size();i++){
            vec.push_back(other.vec[i]);
        }
    }

    //CPY_MOV& operator=(const CPY_MOV& other) = delete;
    // CPY_MOV& operator=(const CPY_MOV& other) {
        
    //     std::cout<<"CPY_MV assignment"<<std::endl;

    //     if(other.vec.size() <= 0){
    //         return *this;
    //     }

    //     if (vec.size() != 0){
    //         vec.clear();
    //     }

    //     for(int i=0;i<other.vec.size();i++){
    //         vec.push_back(other.vec[i]);
    //     }

    //     return *this;
    // }

    // move constructor, if other object is not empty, the steal the resource. don't copy
    CPY_MOV(CPY_MOV&& other) noexcept {
        std::cout<<"CTOR MOVE"<<std::endl;

        if ( other.vec.size() > 0){
            vec.swap(other.vec); // swaps internal buffer. another alternative vec = std::move(other.vec);
                                // but vec = other.vec // does a copy
        }

        //other.vec.clear(); // this is redundant with swap
    }

};


int main() {
    
    std::cout<<"Benchmark CPY and MOV"<<std::endl;
    std::vector<CPY_MOV> cObj(1000000);

    // CPY is slower compared with MOV
    {
        StopWatch sw;
        sw.start_timer();
        std::vector<CPY_MOV> dest = cObj;
        sw.print_duration();
    }

    {
        StopWatch sw;
        sw.start_timer();
        std::vector<CPY_MOV> dest = std::move(cObj);
        sw.print_duration();
    }
    
}

/*
result:
CPY: Duration to finish compute: 3304 milli sec
MOV; Duration to finish compute: 0 milli sec
*/