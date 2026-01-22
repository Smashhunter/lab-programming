#include <cstddef>
#include <cstdlib>
#include <limits>
#include <memory>
#include <type_traits>

#include <iostream>

template <typename T, std::size_t PoolSize = 256>
class SimpleBlockAllocator {
private:
    union Block {
        Block* next;
        typename std::aligned_storage<sizeof(T), alignof(T)>::type data;
    };

    Block pool[PoolSize];
    
    Block* free_list; // Linked list
    
    void init_free_list() {
        free_list = &pool[0];
        for (std::size_t i = 0; i < PoolSize - 1; ++i) {
            pool[i].next = &pool[i + 1];
        }
        pool[PoolSize - 1].next = nullptr;
    }

public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    
    template <typename U>
    struct rebind {
        using other = SimpleBlockAllocator<U, PoolSize>;
    };
    
    SimpleBlockAllocator() noexcept {
        init_free_list();
    }
    
    SimpleBlockAllocator(const SimpleBlockAllocator&) noexcept {
        init_free_list();
    }
    
    T* allocate(std::size_t n) {
        if (n != 1) {
            // Для массивов используем стандартный malloc
            T* ptr = static_cast<T*>(std::malloc(n * sizeof(T)));

            std::cout << "Sorry, using malloc!\n";

            if (!ptr) throw std::bad_alloc();
            return ptr;
        }
        
        if (!free_list) {
            throw std::bad_alloc();  // Пул пуст!
        }
        
        Block* block = free_list;
        free_list = free_list->next;
        
        return reinterpret_cast<T*>(&block->data);
    }
    
    void deallocate(T* ptr, std::size_t n) noexcept {
        if (n != 1) {
            std::free(ptr);
            return;
        }
        
        Block* block = reinterpret_cast<Block*>(ptr);
        // Insert operation in linked list
        block->next = free_list;
        free_list = block;
    }
    
    size_type max_size() const noexcept {
        return PoolSize;  // Максимум PoolSize одиночных объектов
    }
    
    template <typename... Args>
    void construct(T* ptr, Args&&... args) {
        new (ptr) T(std::forward<Args>(args)...);
    }
    
    void destroy(T* ptr) {
        ptr->~T();
    }
};
