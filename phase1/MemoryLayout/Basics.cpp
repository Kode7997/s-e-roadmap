
/*


- sizeof(), alignof(), offsetof()

*/

#include<iostream>
#include<cstdint>

struct Alignment {
    // double d;
    // char c;
    // int i;

    // double d;
    // int b;
    // char a;     // 1byte
    // char c;     // 1 byte

    // uint8_t*   ptr;
    
    uint32_t a1;
    uint32_t a2;
    uint32_t a3;
    uint32_t a4;

    uint16_t a10;

    uint64_t a5;
    uint64_t a6;
    uint64_t a7;
    uint64_t a8;    
    
    int a9;
    
};

class A {
    public:
        A(){}
        ~A() {}

    // uint32_t a1;    // 4,4,4
    // uint32_t a2;
    // uint32_t a3;
    //                 // 12

    // uint16_t a10;   // 2
    //                 // 14 + 2 padding

    // int a9;         // 4 
    //                 // 20 (16 + 4)
    //                 // 20 + 4(padding) = 24

    // uint64_t a5;    // 8,8,8,8
    // uint64_t a6;
    // uint64_t a7;
    // uint64_t a8;
    //                 // 24+32 = 56bytes 

    // uint32_t a11;   // 4    56+4 = 60
    // uint32_t a12;   // 4    60+4 = 64

    // // total size 58bytes + 6 bytes padding
    // // extra 6 bytes


    uint64_t a5;    // 8,8,8,8
    uint64_t a6;
    uint64_t a7;
    uint64_t a8;
                    // 32 bytes


    uint32_t a1;    // 4,4,4,4,4
    uint32_t a2;
    uint32_t a3;
    uint32_t a11;   
    uint32_t a12;   
    //              // 32 + 20 = 52bytes

    
    int a9;         // 4 
                    // 52 + 4 = 56 bytes
    
    uint16_t a10;   // 2
                    // 56 + 2 + 6 (byte padding as it should align to largest memeber of struct which is uint64_t 8 bytes)
                    
};

int main() {

    Alignment aln;

    std::cout<<"size: "<<sizeof(int)<<std::endl;
    // std::cout<<"aligh of a,b,c "<<alignof(aln.a)<<" "<<alignof(aln.b)<<" "<<alignof(aln.c)<<" "<<alignof(aln.d)<<std::endl;
    // std::cout<<"offset of a,b,c "<<offsetof(Alignment, d)<<" "<<offsetof(Alignment, c)<<" "<<offsetof(Alignment, a)<<std::endl;

    // alignas(8) Alignment aln2;
    // std::cout<<"alignment: "<<sizeof(aln2)<<std::endl;
    return 0;
}

