#pragma once

#include <memory>
#include <type_traits>
#include <iterator>
#include <cstddef>

template <
    class T
>
class my_list
{
private:
    struct Node;
    using UniquePtr = std::unique_ptr<Node>;

    struct Node {
        T data;        
        Node* prev;
        UniquePtr next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    UniquePtr head;
    Node* tail;
    size_t size_ = 0;

public:
    class iterator{
    private:
        Node* m_ptr;

    public:
        iterator(Node* ptr) : m_ptr(ptr) {}

        // Переопределяем виртуальные методы
        T& operator*() const { 
            if (!m_ptr) throw std::runtime_error("Dereferencing null iterator");
            return m_ptr->data; 
        }
        
        T* operator->() const  { 
            if (!m_ptr) return nullptr;
            return &m_ptr->data; 
        }
        
        T* ptr() const { 
            return m_ptr ? &m_ptr->data : nullptr;
        }

        // Дополнительные методы для конкретного итератора
        Node* node_ptr() const { return m_ptr; }

        // Операторы инкремента/декремента
        iterator& operator++() { 
            if (m_ptr) m_ptr = m_ptr->next.get(); 
            return *this; 
        }
        
        iterator operator++(int) { 
            iterator tmp = *this; 
            ++(*this); 
            return tmp; 
        }
        
        iterator& operator--() {
            if (m_ptr) m_ptr = m_ptr->prev;
            return *this;
        }
        
        iterator operator--(int) { 
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        iterator operator+(std::ptrdiff_t n) const {
            iterator tmp = *this;
            while (n)
            {
                ++tmp;
                --n;
            }
            
            return tmp; 
        }
        // iterator operator-(difference_type n) const { return iterator(m_ptr - n); }

        friend bool operator==(const iterator& a, const iterator& b) { 
            return a.m_ptr == b.m_ptr; 
        }
        
        friend bool operator!=(const iterator& a, const iterator& b) { 
            return a.m_ptr != b.m_ptr; 
        }
    };

    // Конструкторы
    my_list() = default;  // Default constructor
    
    // Конструктор копирования
    my_list(const my_list& other) {
        for (const auto& item : other) {
            push_back(item);
        }
    }
    
    // Конструктор перемещения
    my_list(my_list&& other) noexcept 
        : head(std::move(other.head)), tail(other.tail), size_(other.size_) {
        other.tail = nullptr;
        other.size_ = 0;
    }
    
    // Конструктор из initializer_list
    my_list(std::initializer_list<T> init) {
        for (const auto& item : init) {
            push_back(item);
        }
    }
    
    // Оператор присваивания копированием
    my_list& operator=(const my_list& other) {
        if (this != &other) {
            clear();
            for (const auto& item : other) {
                push_back(item);
            }
        }
        return *this;
    }
    
    // Оператор присваивания перемещением
    my_list& operator=(my_list&& other) noexcept {
        if (this != &other) {
            clear();
            head = std::move(other.head);
            tail = other.tail;
            size_ = other.size_;
            
            other.tail = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    void clear() {
        while (head) {
            head = std::move(head->next);
        }
        tail = nullptr;
        size = 0;
    }

    void push_back(const T& value) ;

    void push_back(T&& value);

    size_t size() const {
        return size_;
    }
    void erase(iterator pos);

    void erase(iterator first, iterator last);

    void insert(iterator it, const T& value);

    void insert(iterator it, T&& value);

    T& operator [](iterator index) {
        return *index;
    }

    iterator begin() { 
        return iterator(head.get()); 
    }
    
    iterator end() { 
        return iterator(nullptr); 
    }

    std::reverse_iterator<iterator> rbegin() { 
        return std::reverse_iterator<iterator>(end()); 
    }
    
    std::reverse_iterator<iterator> rend() { 
        return std::reverse_iterator<iterator>(begin()); 
    }

};

template <class T>
inline void my_list<T>::push_back(const T &value)
{
    auto newNode = std::make_unique<Node>(value);
    
    if (!head) {
        head = std::move(newNode);
        tail = head.get();
    } else {
        newNode->prev = tail;
        tail->next = std::move(newNode);
        tail = tail->next.get();
    }
    ++size_;
}

template <class T>
inline void my_list<T>::push_back(T &&value)
{
    auto newNode = std::make_unique<Node>(std::move(value));
    
    if (!head) {
        head = std::move(newNode);
        tail = head.get();
    } else {
        newNode->prev = tail;
        tail->next = std::move(newNode);
        tail = tail->next.get();
    }
    ++size_;
}

template <class T>
inline void my_list<T>::erase(iterator pos)
{
    if (!pos.ptr() || size_ == 0) return;

    Node* nodeToDelete = pos.node_ptr();

    if (nodeToDelete == head.get()) {
        // Удаление головы
        head = std::move(head->next);
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
    } else if (nodeToDelete == tail) {
        // Удаление хвоста
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        // Удаление из середины
        Node* prevNode = nodeToDelete->prev;
        Node* nextNode = nodeToDelete->next.get();
        
        prevNode->next = std::move(nodeToDelete->next);
        if (nextNode) {
            nextNode->prev = prevNode;
        }
    }
    --size_;
}

template <class T>
inline void my_list<T>::erase(iterator first, iterator last) 
{
    while (first != last && first != end()) {
        erase(first);
        ++first;
    }
}

template <class T>
inline void my_list<T>::insert(iterator it, const T &value)
{
    if (it == begin()) {
        // Вставка в начало
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(head);
        if (newNode->next) {
            newNode->next->prev = newNode.get();
        }
        head = std::move(newNode);
        if (!tail) tail = head.get();
        ++size_;
    } else if (it == end()) {
        // Вставка в конец
        push_back(value);
    } else {
        // Вставка в середину
        auto newNode = std::make_unique<Node>(value);
        Node* currentNode = it.ptr;
        Node* prevNode = currentNode->prev;
        
        newNode->prev = prevNode;
        newNode->next = std::move(prevNode->next); // CurrentNode
        prevNode->next = std::move(newNode);
        currentNode->prev = prevNode->next.get(); // NewNode
        ++size_;
    }
}

template <class T>
inline void my_list<T>::insert(iterator it, T &&value)
{
    if (it == begin()) {
        // Вставка в начало
        auto newNode = std::make_unique<Node>(std::move(value));
        newNode->next = std::move(head);
        if (newNode->next) {
            newNode->next->prev = newNode.get();
        }
        head = std::move(newNode);
        if (!tail) tail = head.get();
        ++size_;
    } else if (it == end()) {
        // Вставка в конец
        push_back(std::move(value));
    } else {
        // Вставка в середину
        auto newNode = std::make_unique<Node>(std::move(value));
        Node* currentNode = it.node_ptr();
        Node* prevNode = currentNode->prev;
        
        newNode->prev = prevNode;
        newNode->next = std::move(prevNode->next); // CurrentNode
        prevNode->next = std::move(newNode);
        currentNode->prev = prevNode->next.get(); // NewNode
        ++size_;
    }
}
