#include<iostream>

template <class T>
class DynamicArray {

        
    public:

    T *data;
    size_t size;

    DynamicArray() {
        std::cout<<"Default Ctor"<<std::endl;
        data = nullptr;
        size = 0;
    }

    DynamicArray(const T *arr, size_t size) : size(size) {
        data = nullptr;
        std::cout<<"Ctor Dynamic Array"<<std::endl;
        //size = (sizeof(arr)/sizeof(arr[0]));
        std::cout<<"Size: "<<size<<std::endl;
        if (size <= 0) 
        {
            return;
        }

        data = new T[size];
        if (!data){
            return;
        }
        for(int i =0 ; i<size;i++){
            data[i] = arr[i];
        }
    }

    ~DynamicArray() {
        if(data){
            delete[] data;
        }
    }

    // are semantics applicable? Yes
    // allow copy and move
    DynamicArray(const DynamicArray& other) {

        std::cout<<"Copy Ctor"<<std::endl;
        if(other.size <= 0) {
            data = nullptr;
            size = 0;
            return;
        }

        data = new T[other.size];
        size = other.size;

        for(int i=0; i< size; i++){
            data[i] = other.data[i];
        }
    }

    // copy assignment
    // clean old data and allocate new memory and copy

    DynamicArray<T>& operator=(const DynamicArray<T>& other){
        std::cout<<"Copy assignment operator"<<std::endl;
        
        if (this == &other){
            return *this;
        }
        
        if(data != nullptr){
            delete[] data;
            size = 0;
        }

        data = new T[other.size];
        size = other.size;
        for(int i =0;i<other.size;i++) {
            data[i] = other.data[i];
        }

        return *this;
    }


    // move constructor
    // steal the pointer and invalidate the other
    DynamicArray(DynamicArray<T>&& other) noexcept {

        std::cout<<"Move constructor"<<std::endl;
        if(!other.data){
            return;
        }

        if (other.size <=0){
            data = nullptr;
            size = 0;
        }

        data = new T[other.size];
        data = other.data;
        size = other.size;

        other.data = nullptr;
        other.size = 0;

    }
    // move assignment
    // delete old, steal pointer/data/resource and invalidate
    DynamicArray<T>& operator=(DynamicArray<T>&& other) noexcept {

        std::cout<<"Move operator"<<std::endl;
        if(this == &other){
            return *this;
        }

        if(other.size <= 0){
            data = nullptr;
            size = 0;
            return *this;
        }

        data = nullptr;
        size = 0;

        data = new T[other.size];
        size = other.size;
        for(int i=0;i<size;i++){
            data[i] = other.data[i];
        }

        other.data = nullptr;
        other.size = 0;

        return *this;

    }

    void display_data(){
        std::cout<<"Dynamic Array: "<<std::endl;
        if(size<=0){
            std::cout<<"Array is empty"<<std::endl;
            return;
        }
        for(int i=0;i<size;i++){
            std::cout<<data[i]<<" ";
        }
        std::cout<<" "<<std::endl;
    }
};

int main() {
    
    int arr[]  = {1,2,3,4,5};
    DynamicArray<int> da(arr,sizeof(arr)/sizeof(arr[0]));
    da.display_data();

    DynamicArray<int> da1 = da;
    da1.display_data();

    DynamicArray<int> da3;
    da3 = da1;
    da3.display_data();

    DynamicArray<int> da4 = std::move(da3);
    da4.display_data();

    DynamicArray<int> da5;
    da5 = std::move(da1);
    da5.display_data();

    //char c_arr[] = {'h','e','l','l','o'};
    //DynamicArray<char> da2(c_arr,sizeof(c_arr)/sizeof(c_arr[0]));
    //da2.display_data();


}
