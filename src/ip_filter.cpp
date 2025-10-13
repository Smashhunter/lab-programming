#include "ip_filter.hpp"
//split, filter, filter_any


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
