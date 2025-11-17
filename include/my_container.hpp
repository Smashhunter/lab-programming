#pragma once
#include <memory>

template<
    class T,
    class Allocator = std::allocator<T>>
class my_container
{
public:
    struct iterator{
        // Random, Directional, Bidirectional
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;


        virtual reference operator*() const = 0;
        virtual pointer operator->() const = 0;
        virtual pointer ptr() const = 0;
    };
    
    // Description of functions needs to be made:
    // my_container();
    // my_container(const my_container& other)= 0;
    // my_container(my_container&& other) = 0;
    // my_container(std::initializer_list<T> init,
    //     const Allocator& alloc = Allocator() ) = 0;
    
    // virtual my_container& operator =(const my_container& other) = 0;
    // virtual my_container& operator =(const my_container&& other) = 0;
    virtual void push_back(const T& value) = 0;
    virtual void push_back(const T&& value) = 0;
    virtual void print() = 0;
    virtual size_t size() = 0;
    virtual void erase(iterator pos) = 0;
    virtual void erase(iterator first, iterator last) = 0;
    virtual void insert(iterator it, const T& value) = 0;
    virtual void insert(iterator it, const T&& value) = 0;
    virtual T& operator [](size_t index) = 0;
    
    virtual iterator begin() = 0;
    virtual iterator end() = 0;


};
