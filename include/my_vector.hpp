#pragma once

#include <iostream>
#include <memory>

template<class T>
class my_vector
{
private:
    size_t size_ = 0;
    size_t capacity_ = 0;
    std::allocator<T> allocator;
public:
    // my_vector(/* args */);
    // ~my_vector();
    size_t size() const;
};

template <class T>
inline size_t my_vector<T>::size() const
{
    return this->size_;
}
