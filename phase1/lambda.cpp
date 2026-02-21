/*

This file demostrate the lambda function in C++17.
*/

#include <iostream> 
#include <string>
#include <cstdint>

int main() {
    // Lambda function that captures no variables and takes no parameters
    // what does capture no variables mean? It means that the lambda does 
    // not access any variables from the surrounding scope. It can only 
    // use its own parameters and local variables defined within the lambda body.
    
    // 1. print_msg func with no capture and no paramters
    auto print_msg = []() {
        std::cout<<"lambda function with no capture of parameters from surroundings and no internal variables"<<std::endl;
    };

    // Call the lambda function
    print_msg();

    // 2. lambda function that accepts or captures value from surroundings
    std::string name = "lambda";               // 
    auto print_msg_v2 = [name](){
        std::cout<<"Name is: "<< name <<std::endl;
    };
    
    print_msg_v2();

    // 3. lambda function captures surrounding parameters as reference
    int num = 10;
    auto print_msg_v3 = [&num](){
        num = num + 19;
        std::cout<<"Num 10 after addition with 19: "<<num<<std::endl;
    };

    print_msg_v3();
    // 4. lambda function captures surrounding parameters and accepts arguments

    std::string location = "unknown";
    auto print_msg_v4  = [location](int pincode){
        std::cout<<"location: "<<location<<std::endl;
        std::cout<<"pincode: "<<pincode<<std::endl;
    };

    print_msg_v4(584123);

    return 0;
}