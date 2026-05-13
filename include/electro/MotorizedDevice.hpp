#pragma once

#include "electro/AbsractElectroDevice.hpp"
#include <string>

class MotorizedDevice: public AbsractElectroDevice
{
private:
    std::string motorType;
    int rotSpeed;
public:
    std::string GetMotorType();
};
