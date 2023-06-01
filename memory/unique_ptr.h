#ifndef IMPLEMENTING_STL_UNIQUE_PTR_H
#define IMPLEMENTING_STL_UNIQUE_PTR_H
#include <iostream>

namespace impl::memory {

    template<typename T>
    class deleter {
    public:
        static void operator delete(void *ptr) {
            std::cout << " deallocated " << sizeof(T) << " bytes\n";
            free(reinterpret_cast<T*>(ptr));
        }
    };

    template<typename T, typename Deleter = deleter<T>>
    class unique_ptr {
    private:
        T *ptr;

    public:
        unique_ptr(T *n_ptr) : ptr{n_ptr} {};

        unique_ptr(const unique_ptr &) = delete;

        unique_ptr(unique_ptr &&rhs) noexcept: ptr(rhs.ptr) {
            rhs.ptr = nullptr;
        }

        unique_ptr &operator=(const unique_ptr &) = delete;

        unique_ptr &operator=(unique_ptr &&rhs) noexcept {
            ptr = rhs.ptr;
            rhs.ptr = nullptr;
            return *this;
        }

        T& operator*() {
            return *(this->ptr);
        }

        T* operator->() {
            return this->ptr;
        }

        ~unique_ptr() {
            Deleter::operator delete(ptr);
        }
    };
}
#endif //IMPLEMENTING_STL_UNIQUE_PTR_H
