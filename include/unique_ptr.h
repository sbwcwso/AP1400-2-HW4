#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <utility>

template <typename T>
class UniquePtr
{
private:
    T *_p;

public:
    UniquePtr();
    UniquePtr(T *ptr);
    ~UniquePtr();
    UniquePtr(const UniquePtr &other) = delete;
    UniquePtr &operator=(const UniquePtr &other) = delete;
    T* get() const;
    T* release();
    T& operator*() const;
    T* operator->() const;
    void reset(T *p = nullptr);
    explicit operator bool() const;
};

#include "unique_ptr.hpp"
#endif // UNIQUE_PTR