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

int main()
{
    try
    {
        std::vector<std::tuple<int, int, int, int>> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            auto ip = split(v.at(0), '.');
            ip_pool.push_back(std::make_tuple(std::stoi(ip[0]),std::stoi(ip[1]),std::stoi(ip[2]),std::stoi(ip[3])));
        }

        std::sort(ip_pool.begin(), ip_pool.end());
        std::reverse(ip_pool.begin(), ip_pool.end());

        // Output all ip's in reverse lexography
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8
        for(const auto &ip: ip_pool){
            // int a = std::get<0>(ip);
            // std::cout << a;
            std::cout << std::get<0>(ip) << '.' << std::get<1>(ip) << '.' << std::get<2>(ip) << '.' << std::get<3>(ip) << std::endl;
        }
        std::cout << "---------------\n";
        

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8
        for(const auto &ip: ip_pool){
            if(!filter(ip, 1)) continue;
            std::cout << std::get<0>(ip) << '.' << std::get<1>(ip) << '.' << std::get<2>(ip) << '.' << std::get<3>(ip) << std::endl;
        }
        std::cout << "---------------\n";

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        for(const auto &ip: ip_pool){
            if(!filter(ip, 46, 70)) continue;
            std::cout << std::get<0>(ip) << '.' << std::get<1>(ip) << '.' << std::get<2>(ip) << '.' << std::get<3>(ip) << std::endl;
        }
        std::cout << "---------------\n";

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // ...
        // 5.189.203.46
        for(const auto &ip: ip_pool){
            if(!filter_any(ip, 46)) continue;
            std::cout << std::get<0>(ip) << '.' << std::get<1>(ip) << '.' << std::get<2>(ip) << '.' << std::get<3>(ip) << std::endl;
        }
        std::cout << "---------------\n";
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
