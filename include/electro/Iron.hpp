#pragma once

#include "electro/HeatingDevice.hpp"
#include <string>

class Iron: public HeatingDevice
{
private:
    std::string soleplate;
    double vaterTankVolume;
public:
};

