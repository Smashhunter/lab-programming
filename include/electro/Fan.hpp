#pragma once

#include "electro/MotorizedDevice.hpp"

class Fan: public MotorizedDevice
{
private:
    int bladeCount;
    double noiseLevel;
public:
};
