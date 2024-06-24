#ifndef SHARED_PTR
#define SHARED_PTR

#include <utility>


template <typename T>
class SharedPtr
{
    private:
        T *_p;
        int *ref_count;

    public:
        explicit SharedPtr(T *ptr);
        SharedPtr(const SharedPtr<T>& other);
        SharedPtr();
        ~SharedPtr();
        T *get() const;
        T *operator->() const;

        T &operator*() const;
        SharedPtr<T> &operator=(const SharedPtr<T> &other);

        void reset();
        void reset(T *p);

        int use_count();

        explicit operator bool() const;
};

#include "shared_ptr.hpp"
#endif //SHARED_PTR