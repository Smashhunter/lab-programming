#include <vector>
#include <iostream>
#include <string>

#include "my_vector.hpp"
#include "my_list.hpp"
#include "my_container.hpp"
int main(){
    my_vector<int> test;
    for(int i = 0; i < 10; ++i ){
        test.push_back(i);
    }
    for(auto n: test){
        std::cout << n << ' ';
    }
    std::cout << '\n' << "size: " << test.size() << '\n';
    test.erase(test.begin()+2);
    test.erase(test.begin()+3);
    test.erase(test.begin()+4);
    for(auto n: test){
        std::cout << n << ' ';
    }
    std::cout << '\n';
    test.insert(test.begin(), 10);
    for(auto n: test){
        std::cout << n << ' ';
    }
    std::cout << '\n';
    test.insert(test.begin() + (test.size() / 2), 20);
    for(auto n: test){
        std::cout << n << ' ';
    }
    std::cout << '\n';
    test.insert(test.end(), 30);
    for(auto n: test){
        std::cout << n << ' ';
    }
    std::cout << '\n';
}
