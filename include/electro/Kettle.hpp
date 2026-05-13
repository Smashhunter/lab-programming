#pragma once

#include "electro/HeatingDevice.hpp"
#include <string>

class Kettle: public HeatingDevice
{
private:
    double volume;
    std::string bodyMat;
public:
};
