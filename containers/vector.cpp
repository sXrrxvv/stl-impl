#include <iostream>
#include <cstddef>
#include <vector>

//TODO divide to vector.h and vector.cpp
//TODO allocators, iterators, may-be refactor some parts

template <typename T>
class vector{

private:
    T* buf{nullptr};
    size_t cap{0};
    size_t sz{0};

    T* allocate(size_t nSz){
        return reinterpret_cast<T*>(new std::byte[sizeof(T)*nSz]);
    }

    void deallocate(T* ptr){
        delete[] reinterpret_cast<std::byte*>(ptr);
    }

    template <typename U>
    void construct(T* ptr, U&& val){
        new (ptr) T(std::forward<U>(val));
    }

    void reallocate(T* nBuf){
        for(size_t i = 0; i <= sz; ++i){
            try{
                construct(nBuf[i], std::move_if_noexcept(buf[i]));
            }
            catch(...){
                for(size_t j = 0; j <= i; ++j){
                    buf[j] = std::move_if_noexcept(nBuf[i]);
                    nBuf[j].~T();
                }
                throw;
            }
            buf[i].~T();
        }
        deallocate(buf);
    }

public:

    vector()  = default;

    ~vector(){
        delete[] buf;
    }

    explicit vector(size_t nSz, const T& val = T()) : sz(nSz){
        try {
            buf = allocate(sz);
        }
        catch(std::bad_alloc&){
            std::cout << "memory limit exceeded\n";
        }
        for(int i = 0; i < sz; ++i){
            try {
                construct(buf+i, val);
            }
            catch(...){
                std::cerr << "creating value exception caught\n";
                cap = i;
                sz = i;
                throw;
            }
        }
        cap = sz;
    }

    T& operator [](size_t ind) noexcept{
        return buf[ind];
    }

    T operator [](size_t ind) const noexcept{
        return buf[ind];
    }

    vector(const vector& rhs) : sz(rhs.sz), cap(rhs.cap){
        try {
            auto nBuf = allocate(cap);
        }
        catch(std::bad_alloc&){
            std::cout << "memory limit exceeded\n";
        }
        for(int i = 0; i < sz; ++i){
            try {
                new(buf + i) T(rhs[i]);
            }
            catch(...){
                sz = i;
                throw;
            }
        }
    }

    vector(vector&& rhs)  noexcept : cap(rhs.cap), sz(rhs.sz), buf(rhs.buf){
        rhs.buf = nullptr;
        rhs.sz = 0;
        rhs.cap = 0;
    }

    vector& operator = (const vector& rhs){
        if(this == &rhs)
            return *this;
        auto tmp = vector(rhs);
        std::swap(*this, tmp);
        return *this;
    }

    vector& operator = (vector&& rhs) noexcept{
        buf = rhs.buf;
        cap = rhs.cap;
        sz = rhs.sz;
        rhs.buf = nullptr;
        rhs.sz = 0;
        rhs.cap = 0;
    }

    void reserve(size_t nSz){
        if(nSz < cap)
            return;
        T* nBuf;
        try {
            nBuf = allocate(nSz);
        }
        catch (std::bad_alloc&){
            std::cerr << "Memory limit exceeded\n";
            delete[] reinterpret_cast<std::byte*>(nSz);
            throw;
        }
        for(int i = 0; i < sz; ++i){
            try {
                new(nBuf + i) T(std::move_if_noexcept(buf[i]));
            }
            catch(...){
                for(int j = 0; j <= i; ++j){
                    nBuf[j].~T();
                }
                delete[] reinterpret_cast<std::byte*>(nBuf);
                throw;
            }
            buf[i].~T();
        }
        cap = nSz;
        sz = nSz;
        delete[] buf;
        buf = nBuf;
    }

    void resize(size_t nSz, const T& val = T()){
        if(sz == nSz)
            return;
        auto nBuf = allocate(nSz);
        if(sz < nSz){
            for(int i = 0; i < sz; ++i){
                new (nBuf + i) T(std::move_if_noexcept(buf[i]));
                buf[i].~T();
            }
            for(int i = sz; i < nSz; ++i){
                new (nBuf + i) T(val);
            }
        }
        else{
            for(int i = 0; i < nSz; ++i){
                new (nBuf + i) T(std::move_if_noexcept(buf[i]));
                buf[i].~T();
            }
        }
        sz = nSz;
        cap = nSz;
        delete[] buf;
        buf = nBuf;
    }

    template <typename... Args>
    void emplace_back(Args&&... args){
        if(sz < cap){
            new (buf + sz) T(std::forward<Args>(args)...);
            ++sz;
        }
        else {
            auto nBuf = allocate(cap == 0 ? 1 : 2*cap);
            for (size_t i = 0; i < cap; ++i) {
                new(nBuf + i) T(std::move_if_noexcept(buf[i]));
                buf[i].~T();
            }
            delete[] buf;
            new(nBuf + cap) T(std::forward<Args>(args)...);
            cap = (cap == 0 ? 1 : 2*cap);
            ++sz;
            buf = nBuf;
        }
    }

    template<typename U>
    void push_back(U&& val){
        this->emplace_back(val);
    }

    [[nodiscard]] constexpr size_t size() const noexcept{
        return sz;
    }

    [[nodiscard]] constexpr size_t capacity() const noexcept{
        return cap;
    }

    void pop_back() {
        buf[sz-1].~T();
        --sz;
    }

    T& back(){
        return buf[sz- 1];
    }

    //iterators
    class iterator : public std::random_access_iterator_tag{
    private:
        T* ptr{nullptr};

    public:
        T& operator *(){
            return *ptr;
        }

        T operator ->() {
            return ptr;
        }


    };
};


