#pragma once
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <stdarg.h>

using Octs = std::tuple<int, int, int, int>;


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


bool filter(const Octs &ip, 
    int oct1=-1, 
    int oct2=-1,
    int oct3=-1, 
    int oct4=-1)
{
    return  ((oct1 == -1) || (oct1 == std::get<0>(ip))) &&
            ((oct2 == -1) || (oct2 == std::get<1>(ip))) &&
            ((oct3 == -1) || (oct3 == std::get<2>(ip))) &&
            ((oct4 == -1) || (oct4 == std::get<3>(ip)));
}


bool filter_any(const Octs &ip, int value=-1){
    return  std::get<0>(ip)==value ||
            std::get<1>(ip)==value ||
            std::get<2>(ip)==value ||
            std::get<3>(ip)==value;
}   
