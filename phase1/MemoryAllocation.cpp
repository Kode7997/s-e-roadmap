#include <iostream>
#include <vector>

/*
Note:
1. Max stack size varies from 1MB ~ 8MB. check the size using ulimit -s
    - Stack size can be increased but large data must be stored in heap to avoid OVERFLOW
    - To increase the stack size ulimit -s 16400 ~ 16MB
2. Problem with not following stack/heap dicipline
    - Stack overflow
    - Double delete will lead to crash
    - Accessing deleted ptr can lead to undefined behaviour or crash
    - Memory LEAK
3. To avoid resource leaks in the program few techniques can be followed as below
    3.1 RAII
        - Tie resource lifetime with object lifetime
            * constructor - acquires the resource(open file, acquire memory, lock mutex, sockets)
            * destructor - release the resource( close file, free memory, unlock mutex, release sockets)
    3.2 SMART Pointer
        - unique_ptr, shared_ptr, weak_ptr
4.  Destructor Semantics
    4.1 Trivial and Non-Trivial Destructors
        4.1.1. Trivial Destructor
                - Compiler creates non-trivial destructor sometimes not required as objects are cleaned after lifetime ends
        4.1.2. Non-Trivial Destrictors
                - User defined destructor which are required to cleanup the objects
    4.2 When and how destructor called?
        - Destructor are called when object lifetime ends i.e when scope of object ends
        - Called in the reverse order of constructor call becuase of last class may depend on previous class
        - Destructor may not be called when there are exception in the constructor as object creation itself is not succesful
5. Rule of 5 in Modern CPP (C++11)
    - If Class is owns any resources, developer must define following 5 members
        i. Destructor ~T() - to free resource
        ii. Copy Construct T(const T&) -- Deep Copy
        iii. Copy Assignment T& operator=(const T&) -- Deep copy
        iv. Move Constructor T(const T&&) -- steal Resources(C++11)
        v. Move Assignment T& operator=(T&&) --steal Resources(C++11)
*/


int main()
{
    int x = 0;      //memory allocated in stack
    int y = 0;      //memory allocated in stack and continuous
    std::cout<<"Addr of x and y: "<<&x<<" "<<&y<<std::endl;

    std::vector<int> vec;  // memory allocated in stack
    vec.push_back(10);     // But memory allocated for data in vector is in heap

    int z = 10;     //stack memory
    int *ptr = &z;  //pointer points to address of var z;

    int *ptr1 = new int(2); //allocation in heap
    int *ptr2 = new int[100]; //allocation in heap

    delete ptr1;    //manual cleanup. must return memory to allocator else will cause MEMORY LEAK
    delete[] ptr2;  //manual cleanup. if not cleaned then will cause LEAK

    return 0;
}