#include "my_vector.hpp"
#include <vector>

int main(){
    std::vector<int> test2(1,0);
    my_vector<int> test;
    std::cout << test.size() << ' ' << test2.size() << '\n';
}
