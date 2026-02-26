/*
String Class
    - demonstrate rule of 5
*/

#include<iostream>
#include<utility>
#include<string>

class String{
    char *string_;
    size_t size_;

    public:
        explicit String(std::string s): size_(s.length())
        {
            string_ = new char[size_ + 1];
            
            // for(int i=0;i<size_;i++){
            //     string_[i] = s[i];
            // }
            strcpy(string_, s.c_str());  // Easier than loop

            std::cout<<"string_: "<<string_<<" size: "<<size_<<std::endl;
        }
        
        // Destructor
        ~String()
        {
            if(size_ >= 0){
                delete[] string_;

                std::cout<<"Destroyed object "<<this<<" to avoid memory leaks"<<std::endl;
            }
        }
        // Copy constructor
        String(const String& other):string_(nullptr), size_(0) {
            
            std::cout<<"Copy Construct"<<std::endl;

            if(other.size_ < 0) return;

            this->size_ = other.size_;
            this->string_ = new char[size_ + 1];
            strcpy(this->string_, other.string_);

            std::cout<<"Copy Constructor called: copied object string_: "<<this->string_<<std::endl;
        }

        // Copy assignment
        String& operator=(const String& other) {
            std::cout<<"Copy Assginment"<<std::endl;
            std::cout<<"String before copy assignment: "<<this->string_<<std::endl;

            if(this == &other) return *this;

            
            if(this->size_ > 0){
                delete[] this->string_;
                this->string_ = nullptr;
                this->size_ = 0;
            }

            this->size_ = other.size_;
            this->string_ = new char[size_ + 1];

            strcpy(this->string_, other.string_);
            std::cout<<"String copy assignment: "<<this->string_<<std::endl;
            return *this;
        }

        // // move constructor
        String(String&& other) noexcept {

            if (other.size_ > 0){
                this->size_ = other.size_;
                //this->string_ = new char[this->size_ + 1]; // In move NO creation is allowed. only change the pointer
                this->string_ = other.string_;
            }

            other.size_ = 0;
            other.string_ = nullptr;

            std::cout<<"moved string: "<<this->string_<<std::endl;
        }

        
        // // move assignment
        String& operator=(String&& other) noexcept {

            if(this == &other) return *this;

            if(this->size_ > 0) {      // free the old data in heap memory else mem leak
                delete[] this->string_;
                this->string_ = nullptr;
            }

            if (other.size_ > 0){
                this->size_ = other.size_;
                this->string_ = other.string_; // steal the pointer
            }

            other.size_ = 0;
            other.string_ = nullptr;

            std::cout<<"move assignment string: "<<this->string_<<std::endl;

            return *this;
        }

};

int main()
{
    String s("Hello");
    String s1 = s;      // copy constructor
    String s3("world");

    s3 = s1; // copy assignment

    String s5("Move");
    s5 = std::move(s);

    // move constructor
    String s4 = std::move(s1);   // lvalue to rvalue

    int a;
    std::cin>>a;

    return 0;
}