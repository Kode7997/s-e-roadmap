
/*
    Build dynamic array with full move support
*/

#include <iostream>
#include <utility>

class DynArray {
    int* data_;
    size_t size_;
    
public:
    // Constructor
    DynArray(size_t size = 0) : size_(size) {
        data_ = size_ > 0 ? new int[size_] : nullptr;
        std::cout << "Constructor (size: " << size_ << ")\n";
    }
    
    // TODO: Implement
    // 1. Destructor

    ~DynArray(){
        std::cout<<"Destructor called"<<std::endl;

        if (data_){
            delete[] data_;
        }
    }
    // 2. Copy constructor
    DynArray(const DynArray& other): size_(other.size_), data_(nullptr){
        
        if(other.size_ == 0) return;    // though it returns data_ is nullptr avoids UB or Crash

        data_ = new int[size_];
        for(int i=0;i<size_;i++){
            data_[i] = other.data_[i];
        }
    }

    // 3. Copy assignment
    DynArray& operator=(const DynArray& other) {
        if(this == &other) return *this;

        // delete old data first
        data_ = nullptr;
        size_ = 0;
        
        if (other.size_ > 0){
            size_ = other.size_;
            data_ = new int[size_];

            for(int i=0;i<size_;i++)
            {
                data_[i] = other.data_[i];
            }
        }

        return *this;
    }

    // 4. Move constructor - should steal the pointer but not copy
    DynArray(DynArray&& other) noexcept : size_(other.size_), data_(other.data_) {          // noexcept is must as it guarantees caller that there will
                                                                                            // no exception during move else it may corrupt original source
        other.data_ = nullptr;  // other cannot be const because it is being modified in move.
        other.size_ = 0;
    }

    // 5. Move assignment
    DynArray& operator=(DynArray&& other) noexcept {
        
        if(this == &other) return *this;
        
        delete[] data_;

        // steal the pointer
        data_ = other.data_;
        size_ = other.size_;

        // invalidate the source
        other.data_ = nullptr;
        other.size_ = 0;
        
        return *this;
    }
    
    void print() const {
        std::cout << "Size: " << size_ << ", Data: " << (data_ ? "valid" : "null") << "\n";
    }
};

int main() {
    DynArray a1(10);              // Constructor
    DynArray a2 = a1;             // Copy constructor
    DynArray a3 = std::move(a1);  // Move constructor
    
    a2 = a3;                      // Copy assignment
    a2 = std::move(a3);           // Move assignment
    
    a1.print();  // Should show null/0
    a2.print();  // Should show valid data
    a3.print();  // Should show null/0 (moved from)
}

