
/*
This file explain unique_ptr, it's capabailities and use-cases

- One owner access memory at a time. when owner destroyed memory is freed.
- Give exclusive ownership to a pointer no other can access reserved memory
- No COPY allowed (unique_ptr)
- Move is allowed to transfer the ownership
- Overhead of deleting the resource is eased. As destructor is called automcatically which eventually solves MEM LEAK problem
- Avoids multiple returns

*/

#include<iostream>
#include<memory>

class Resource {

    public:
        int id_;
        Resource(int id): id_(id) {
            std::cout<<"Resource Ctor"<<std::endl;
        }

        ~Resource(){
            std::cout<<"Resource Dtor"<<std::endl;
        }

        int getId() {
            return id_;
        }

        void setId(int id) {
            id_ = id;
        }

        void display() {
            std::cout<<"Resource id: "<<id_<<" and it's address: "<<this<<std::endl;
        }
};

int main() {

    // unique_ptr: no copy will occur but move can be used to transfer the ownership
    std::unique_ptr<Resource> ptr(new Resource(1));
    
    // std::cout<<"Resource address: "<<&ptr<<std::endl;
    // std::cout<<"Resource value: "<<ptr->id_<<std::endl;
    ptr->display();

    std::cout<<"Resource modify to 10: "<<std::endl;
    ptr->setId(10);
    ptr->display();

    std::unique_ptr<Resource> resource_ptr(std::move(ptr)); // resource_ptr must be of type unique_ptr and accepts rvalue
    resource_ptr->display();
    //std::unique_ptr<Resource> resource_ptr2 = resource_ptr; //Error: no copy is allowed


    // make_unique pointer - this exception safety and atomic operation 
    std::unique_ptr<Resource> resource = std::make_unique<Resource>(2);

    // ownership behaviour when it is passed as a function
    /*
    Different types:
        1. Take ownership when resource passed as a parameter to function
        2. Borrow and without OWNing resource
        3. Borrow via reference 

        // Other functionalities and it's behaviour
        4. With arrays:
            e.g: std::unique_ptr<[]> arr(new int[10])
                while deletion it calls delete[] and NOT delete
                Also applicable make_unique likewise
                auto arr = std::make_unique<int[]>(10);
        5. custom deleter
        6. release and reset
            release: relinquish ownership but not delete. used when handing over to raw pointer
            reset: delete and assign to new
        7. polymorphism
        8. Move to containers
            std::vector<std::uniqie_ptr<Resource>> resources;
            resource.push_back(std::make_unique<Resource(10));
        */

    // e.g: for 1
    auto take_ownership = [](std::unique_ptr<Resource> ptr) {
        std::cout<<"Lambda func \"taken_ownership\" has Taken Owner from other resource"<<std::endl;
        //std::cout<<"Resource id: "<<ptr->id_<<" and it's address: "<<&ptr<<std::endl;
        ptr->display();
    };

    take_ownership(std::move(resource));

    // e.g: for 2
    auto borrow = [](Resource *ptr1) {
        std::cout<<"Borrowed but not owned"<<std::endl;
        //std::cout<<"borrowed ptr1: "<<ptr1->id_<<" and it's address: "<<ptr1<<std::endl;
        ptr1->display();
    };

    auto borrow_ptr = std::make_unique<Resource>(100);
    std::cout<<"borrow_ptr.get: "<<borrow_ptr.get()<<std::endl;
    borrow(borrow_ptr.get());

    // e.g: for 3
    auto borrow_ref = [](Resource& ref){
        std::cout<<"Borrow resource as a refernce"<<std::endl;
        ref.display();
    };

    auto borrow_ref_obj = std::make_unique<Resource>(200);
    borrow_ref(*borrow_ptr);

    // e.g: for 5 - custom deleter
    auto custom_deleter = [](Resource* ptr) {
        std::cout << "Custom deleter invoked for resource id: " << ptr->getId() << std::endl;
        delete ptr;
    };

    std::unique_ptr<Resource, decltype(custom_deleter)> custom_resource(
        new Resource(300),
        custom_deleter
    );
    custom_resource->display();

    return 0;
}