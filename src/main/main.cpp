#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <functional>

#include "my_vector.hpp"
#include "my_allocator.hpp"

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

int main() {
    std::map<int, int>test1;
    int fact= 1;
    test1[0] = 1;
    for(int i = 1; i < 10; i++){
        fact *= i;
        test1[i] = fact;
    }
    for(const auto [n, n_fact] : test1){
        std::cout << n << ": " << n_fact << std::endl;
    }

    std::cout << "Test2:\n";

    std::map<int, int, std::less<int>, SimpleBlockAllocator<std::pair<int,int>, 10u>> test2;
    fact= 1;
    test2[0] = 1;
    for(int i = 1; i < 10; i++){
        fact *= i;
        test2[i] = fact;
    }
    for(const auto [n, n_fact] : test2){
        std::cout << n << ": " << n_fact << std::endl;
    }


    my_vector<int, SimpleBlockAllocator<int>> v;

    for(int i = 1; i <= 10; i++){
        v.push_back(i);
    }

    for(auto num: v){
        std::cout << num << ' ';
    }
    std::cout << std::endl;

    //Additional tests for alloc work check in debbuger

    SimpleBlockAllocator<Point, 4> alloc;  // 4 Block sized pool
    
    std::cout << "1. Init pool:\n";
    // Pool: [0]→[1]→[2]→[3]→nullptr
    
    Point* p1 = alloc.allocate(1);
    alloc.construct(p1, 1, 2);
    std::cout << "p1 в блоке 0: (" << p1->x << "," << p1->y << ")\n";
    // Pool: [0 object]   [1]→[2]→[3]→nullptr
    
    Point* p2 = alloc.allocate(1);
    alloc.construct(p2, 3, 4);
    std::cout << "p2 в блоке 1: (" << p2->x << "," << p2->y << ")\n";
    // Pool: [0 object] [1 object] [2]→[3]→nullptr
    
    alloc.destroy(p1);
    alloc.deallocate(p1, 1);
    std::cout << "Освободили p1 (блок 0)\n";
    // Pool: [0]→[2]→[3]→nullptr   [1 object]
    
    Point* p3 = alloc.allocate(1);
    alloc.construct(p3, 5, 6);
    std::cout << "p3 в блоке 0: (" << p3->x << "," << p3->y << ")\n";
    // Pool: [0 object] [1 object] [2]→[3]→nullptr
    
    return 0;
}
