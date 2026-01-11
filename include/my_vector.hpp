#pragma once

#include <iostream>
#include <memory>
#include <type_traits>
#include <iterator>
#include <cstddef>
#include <iostream>

template<
    class T, 
    class Allocator = std::allocator<T>>
class my_vector
{
private:
    using AllocTraits = std::allocator_traits<Allocator>;

    struct AllocDeleter {
        Allocator* alloc;
        size_t count;

        AllocDeleter(Allocator* a = nullptr, size_t n = 0)
            : alloc(a), count(n) {}
        
        void operator()(T* ptr){
            if(ptr && alloc){
                for(size_t i = count; i>0; --i){
                    AllocTraits::destroy(*alloc, ptr + i - 1);
                }
                AllocTraits::deallocate(*alloc, ptr, count);
            }
        }
    };
    
    using UniquePtr = std::unique_ptr<T[], AllocDeleter>;

    UniquePtr data_;
    size_t size_ = 0;
    size_t capacity_ = 0;
    Allocator alloc_;

public:
    struct iterator{
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        iterator(pointer ptr): m_ptr(ptr){}

        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }
        pointer ptr() const { return m_ptr; }

        iterator& operator++() { ++m_ptr; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++m_ptr; return tmp; }
        iterator& operator--() { --m_ptr; return *this; }
        iterator operator--(int) { iterator tmp = *this; --m_ptr; return tmp; }
        
        iterator operator+(difference_type n) const { return iterator(m_ptr + n); }
        iterator operator-(difference_type n) const { return iterator(m_ptr - n); }
        difference_type operator-(const iterator& other) const { return m_ptr - other.m_ptr; }

        friend bool operator==(const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!=(const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; }

    private:
        pointer m_ptr;
    };
    
    //Default constuctor
    my_vector()
        : data_(nullptr, AllocDeleter(&alloc_, 0)) {}

    //Copy constructor
    my_vector(const my_vector& other)
        : alloc_(other.alloc_) 
        , size_(other.size_)
        , capacity_(other.size_)
    {
        if (other.size_ > 0) {
            T* new_data = AllocTraits::allocate(alloc_, capacity_);
            try {
                std::uninitialized_copy_n(other.data_.get(), size_, new_data);
            } catch (...) {
                AllocTraits::deallocate(alloc_, new_data, capacity_);
                throw;
            }
            data_.reset(new_data);
            data_.get_deleter().count = size_;
        }
    }
    
    //Move constuctor
    my_vector(my_vector&& other)
        : data_(std::move(other.data_))
        , size_(other.size_)
        , capacity_(other.capacity_)
        , alloc_(std::move(other.alloc_))
    {
        other.size_ = 0;
        other.capacity_ = 0;
        other.data_.reset(nullptr);
    }

    //Init list ({...}) constuctor
    my_vector(std::initializer_list<T> init,
        const Allocator& alloc = Allocator() )
        : alloc_(alloc)
        , size_(init.size())
        , capacity_(init.size())
    {
        if (size_ > 0) {
            T* new_data = AllocTraits::allocate(alloc_, capacity_);
            try {
                std::uninitialized_copy(init.begin(), init.end(), new_data);
            } catch (...) {
                AllocTraits::deallocate(alloc_, new_data, capacity_);
                throw;
            }
            data_.reset(new_data);
            data_.get_deleter() = AllocDeleter(&alloc_, size_);
        } else {
            data_ = UniquePtr(nullptr, AllocDeleter(&alloc_, 0));
        }
    }

    // Copy operator
    my_vector& operator =(const my_vector& other)
   {
        if (this != &other) {
            my_vector temp(other);
            *this = std::move(temp);
        }
        return *this;
    }

    // Move operator
    my_vector& operator =(const my_vector&& other)
    {
        if (this != &other) {
            // Free resources
            data_.reset();
            size_ = 0;
            capacity_ = 0;

            // Move
            data_ = std::move(other.data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            alloc_ = std::move(other.alloc_);
            
            // Make other null
            other.size_ = 0;
            other.capacity_ = 0;
            other.data_.reset(nullptr);
        }
        return *this;
    }

    void reserve(size_t new_capacity);
    void push_back(const T& value);
    void push_back(T&& value);
    size_t size() const{
        return size_;
    }
    void erase(iterator pos);
    void erase(iterator first, iterator last);
    void insert(iterator it, const T& value);
    void insert(iterator it, T&& value);
    T& operator [](size_t index){
        if (index < 0 && index >= size_) throw std::out_of_range("Used invalid index for vector");
        return data_[index];
    }

    iterator begin(){
        return iterator(data_.get());
    }
    iterator end(){
        return iterator(data_.get()+size_);
    }

};

template <class T, class Allocator>
inline void my_vector<T, Allocator>::reserve(size_t new_capacity)
{
    if(new_capacity <= capacity_) return;

    T* new_data = AllocTraits::allocate(alloc_, new_capacity);
    
    for(size_t i = 0; i < size_; ++i) {
        alloc_.construct(new_data + i, std::move(data_[i]));
        alloc_.destroy(data_.get() + i);
    }

    data_.reset(new_data);
    data_.get_deleter().count = new_capacity;
    capacity_ = new_capacity;
}

template <class T, class Allocator>
inline void my_vector<T, Allocator>::push_back(const T &value)
{
    if (size_ >= capacity_) {
        reserve(capacity_ ? capacity_ * 2 : 1);
    }
    alloc_.construct(data_.get() + size_, value);
    ++size_;
}

template <class T, class Allocator>
inline void my_vector<T, Allocator>::push_back(T&& value)
{
    if (size_ >= capacity_) {
        reserve(capacity_ ? capacity_ * 2 : 1);
    }
    alloc_.construct(data_.get() + size_, std::move(value));
    ++size_;
}

template <class T, class Allocator>
inline void my_vector<T, Allocator>::erase(iterator pos)
{
    alloc_.destroy(pos.ptr());
    for(size_t i = pos.ptr() - data_.get(); i < size_-1; ++i){
        data_[i] = std::move(data_[i + 1]);
    }
    --size_;
}

template <class T, class Allocator>
inline void my_vector<T, Allocator>::erase(iterator first, iterator last)
{
    size_t shift = last.ptr() - first.ptr();
    for(size_t i = first.ptr() - data_.get(); i < size_- shift + 1; ++i){
        data_[i] = std::move(data_[i + shift]);
    }
    size_ -= shift;
}

template <class T, class Allocator>
inline void my_vector<T, Allocator>::insert(iterator it, const T &value)
{
    size_t index = it.ptr() - data_.get();

    if (size_ >= capacity_)
        reserve(capacity_ ? capacity_ * 2 : 1);
    if (it == (*this).end()) {
        push_back(value);
        return;
    }
    //Shift all elements to iterator pos
    for (size_t i = size_ - 1; i > index; --i) {
        data_[i] = std::move(data_[i - 1]);
    }
    data_[index] = value;

    ++size_;

}

template <class T, class Allocator>
inline void my_vector<T, Allocator>::insert(iterator it, T&& value)
{
    size_t index = it.ptr() - data_.get();

    if (size_ >= capacity_)
        reserve(capacity_ ? capacity_ * 2 : 1);
    if (it == (*this).end()) {
        push_back(std::move(value));
        return;
    }
    //Shift all elements to iterator pos
    for (size_t i = size_ - 1; i > index; --i) {
        data_[i] = std::move(data_[i - 1]);
    }
    data_[index] = std::move(value);

    ++size_;
}
