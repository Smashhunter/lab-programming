#pragma once

#include "electro/AbsractElectroDevice.hpp"

class HeatingDevice: public AbsractElectroDevice
{
private:
    double maxTemp;
public:
    double GetMaxTemp();
};
