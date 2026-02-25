// Phase 1 — Week 1: RAII Wrapper for FILE*
// Demonstrates: RAII, custom deleter, unique_ptr, move semantics
// Acceptance: Valgrind clean, no resource leaks, ownership clear in API

#include <cstdio>
#include <memory>
#include <utility>
#include <stdexcept>
#include <string>
//#include <unistd.h>

// Custom deleter — ensures fclose is called on destruction
struct FileCloser {
    void operator()(FILE* f) const noexcept {
        if (f) std::fclose(f);
    }
};

// RAII file handle — move-only, no copies
using FilePtr = std::unique_ptr<FILE, FileCloser>;

FilePtr open_file(const char* path, const char* mode) {
    FILE* f = std::fopen(path, mode);
    if (!f) {
        throw std::runtime_error(
            std::string("Failed to open file: ") + path);
    }
    return FilePtr(f);
}

// RAII wrapper for POSIX file descriptor
class FileDescriptor {
    int fd_ = -1;
public:
    explicit FileDescriptor(int fd) noexcept : fd_(fd) {}
    ~FileDescriptor() { 
    //    if (fd_ >= 0) ::close(fd_); 
    }

    // Move-only
    FileDescriptor(FileDescriptor&& other) noexcept
        : fd_(std::exchange(other.fd_, -1)) {}
    FileDescriptor& operator=(FileDescriptor&& other) noexcept {
        if (this != &other) {
            // if (fd_ >= 0) ::close(fd_);
            // fd_ = std::exchange(other.fd_, -1);
        }
        return *this;
    }

    // No copies
    FileDescriptor(const FileDescriptor&) = delete;
    FileDescriptor& operator=(const FileDescriptor&) = delete;

    int get() const noexcept { return fd_; }
    explicit operator bool() const noexcept { return fd_ >= 0; }
};

int main() {
    auto f = open_file("test.txt", "w");
    std::fprintf(f.get(), "Hello RAII\n");
    // f automatically closed here — no leak possible
    return 0;
}