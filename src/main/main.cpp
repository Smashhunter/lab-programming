#include"electro/Kettle.hpp"
#include"electro/Iron.hpp"
#include"electro/Fan.hpp"
#include<iostream>

int main(){
    Fan f1;
    Iron I1;
    Kettle K1;
    std::cout << f1.getName() << ' ' << I1.getName() << ' ' << K1.getName() << std::endl;
    return 0;
}
