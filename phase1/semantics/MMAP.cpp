/*
Refer MMAP.md for more details on memory mapped files

Implement mmap with RAII
- Constructor
- Destructor 
- No copy constructor
- No copy assignment
- move constructor
- move assignment
- benchmark w/ mmap and w/o mmap

utilities:
- read
- write
- seek
- get
*/

#include "benchmark.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

class MMAP {

    void *addr_; // address of the memory location mapped
    size_t size_; // size of the location needed
    int fd_;

    public:    
    
    // <sys/mman.h> PROT_READ, PROT_WRITE, PROT_EXEC, PROT_NONE
    explicit MMAP(const char* path, int flag = O_RDONLY, int prot = PROT_READ)
        : addr_(nullptr), size_(0), fd_(-1) {
            
        int fd_ = open(path, flag & ~(O_CREAT | O_EXCL | O_WRONLY), 0644);
        
        if(fd_ < 0) {
            throw std::runtime_error("Failed to open file. file path: " +std::string(path)+" Error: " + strerror(errno));
        }
        
        // Get file size
        struct stat sb;
        if(fstat(fd_, &sb) < 0) {
            close(fd_);
            throw std::runtime_error("Failed to stat file\n");
        }

        // if file is empty then release resource
        size_ = sb.st_size;
        if(size_ == 0){
            close(fd_);
            throw std::runtime_error("Cannot map empty file to memory space");
        }

        // map the file to memory
        addr_ = mmap(nullptr, size_, prot, MAP_SHARED, fd_, 0);
        if(addr_ == nullptr){
            close(fd_);
            throw std::runtime_error("Failed to map file to memory\n");
        }
        
        std::cout<<"MMAP Ctor"<<std::endl;

    }

    // Direct construction from existing file descriptor
    MMAP(void *addr, size_t size, int fd) 
        :addr_(addr), size_(size), fd_(fd) {
        
        std::cout<<"MMAP Ctor (Wrap)"<<std::endl;    
    }
    

    ~MMAP() {

        if (addr_ && addr_ != MAP_FAILED) {
            munmap(addr_, size_);
            addr_ = nullptr;
            std::cout<<"Mem unmapped"<<std::endl;
        }

        if (fd_ >=0 ) {
            close(fd_);
            fd_ = -1;
        }

        std::cout<<"MMAP Dtor"<<std::endl;
    }

    // No Copy Ctor
    MMAP(const MMAP& other) = delete;

    // No Copy Assignment
    MMAP& operator=(const MMAP& other) = delete;

    // Move Ctor
    MMAP(MMAP&& other) noexcept
        : addr_(other.addr_), size_(other.size_), fd_(other.fd_) {
        
        // make the other invalid
        other.addr_ = nullptr;
        other.size_ = 0;
        other.fd_ = -1;
    }

    MMAP& operator=(MMAP&& other) noexcept {

        if(this == &other) return *this;

        // Cleanup current mapping
        if(addr_ && addr_ != MAP_FAILED) {
            addr_ = nullptr;
            fd_ = -1;
            size_ = 0;
        }

        // steal the other
        addr_ = other.addr_;
        fd_ = other.fd_;
        size_ = other.size_;

        // clean the other
        other.addr_ = nullptr;
        other.fd_ = -1;
        other.size_ = 0;

        return *this;
    }


    // UTILITIES
    // getters of fd, addr, size
    // get data
    const void* get() const noexcept {
        return addr_;
    }

    size_t size() const noexcept {
        return size_;
    }

    int get_fd() const noexcept {
        return fd_;
    }

    // mutable
    char* data() noexcept {
        return static_cast<char*>(addr_);
    }

    // mutable
    std::string to_string() {
        return std::string(data(), size_);
    }
};

// Test 1: Basic mmap RAII
void test_1_basic_mmap() {
    
    std::cout<<"TEST 1: Basic Mmap - Automatic Unmapping"<<std::endl;
    
    // Create test file with data
    {   
        std::cout<<"Compute WRITE"<<std::endl;
        StopWatch sw;
        int fd = open("test_mmap.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        const char* data = "Hello from mmap! This is memory-mapped file content.";
        write(fd, data, strlen(data));
        close(fd);
        sw.print_duration();
    }
    
    // Map and read
    {   
        std::cout<<"Compute READ"<<std::endl;
        StopWatch sw;
        sw.start_timer()
        MMAP mmap("test_mmap.txt");
        std::cout << "Content: " << mmap.to_string() <<std::endl;
        sw.print_duration();
    }

    {
        int fd = open("test_mmap.txt", O_RDONLY);
        std::cout<<"Traditional READ using Syscall"<<std::endl;

        char buffer[4096];

        StopWatch sw1;

        sw1.start_timer()
        while(true){
            ssize_t n = read(fd, buffer, sizeof(buffer));
            
            if(n<=0) {
                break;
            }
            
            std::cout<<"Traditional Read: "<<buffer<<std::endl;
        }
        sw1.print_duration();
        close(fd); 
    }
    
    std::cout << "File automatically unmapped after scope exit\n";
}


int main() {

    test_1_basic_mmap();

    return 0;
}

