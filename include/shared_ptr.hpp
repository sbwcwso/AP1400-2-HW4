#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include "shared_ptr.h"

template <typename T>
SharedPtr<T>::SharedPtr(T *ptr) : _p(ptr), ref_count(new int(1))
{
    if (ptr == nullptr)
        *ref_count = 0;
}

template <typename T>
SharedPtr<T>::SharedPtr() : _p(nullptr), ref_count(new int(0))
{
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr &other): _p(other._p), ref_count(other.ref_count)
{
    (*ref_count)++;
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    if (ref_count != nullptr && --(*ref_count) == 0)  // 🌟🌟
    {
        delete _p;
        delete ref_count;
    }

    _p = nullptr;
    ref_count = nullptr;
}

template <typename T>
T *SharedPtr<T>::get() const
{
    return _p;
}

template <typename T>
T *SharedPtr<T>::operator->() const
{
    return _p;
}

template <typename T, typename... Args>
SharedPtr<T> make_shared(Args &&...args)
{
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
T& SharedPtr<T>::operator*() const
{
    return *_p;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T> &other) 
{
    if (this != &other) 
    {
        if (--(*ref_count) == 0)
        {
            delete _p;
            delete ref_count;
        }
        _p = other._p;
        ref_count = other.ref_count;
        (*ref_count)++;
    }
    return *this;
}

template <typename T>
int SharedPtr<T>::use_count()
{
    if (ref_count == nullptr)
        return 0;
    return *ref_count;
}

template <typename T>
SharedPtr<T>::operator bool() const
{
    return _p != nullptr;
}

template <typename T>
void SharedPtr<T>::reset()
{
    delete _p;
    _p = nullptr;
    *ref_count = 0;
}

template <typename T>
void SharedPtr<T>::reset(T *p)
{
    delete _p;
    if (p != nullptr)
    {
        _p = p;
        *ref_count = 1;
    }
}

#endif // SHARED_PTR_HPP