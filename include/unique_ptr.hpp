#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include "unique_ptr.h"

template <typename T>
UniquePtr<T>::UniquePtr() : _p(nullptr)
{
}

template <typename T>
UniquePtr<T>::~UniquePtr()
{
    delete _p;
    _p = nullptr;
}

template <typename T>
UniquePtr<T>::UniquePtr(T *ptr) : _p(ptr)
{
}

template <typename T>
T *UniquePtr<T>::get() const
{
    return _p;
}

template <typename T>
T *UniquePtr<T>::release()
{
    T *temp = _p;
    _p = nullptr;
    return temp;
}

template <typename T, typename... Args>
UniquePtr<T> make_unique(Args &&...args)
{
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
T& UniquePtr<T>::operator*() const
{
    return *_p;
}

template <typename T>
T* UniquePtr<T>::operator->() const
{
    return _p;
}

template <typename T>
void UniquePtr<T>::reset(T* p) 
{
    if (p != _p) 
    {
        delete _p;
        _p = p;
    }
}

template <typename T>
UniquePtr<T>::operator bool() const
{
    return _p != nullptr;
}

#endif // UNIQUE_PTR_HPP
