#pragma once

#include <string>

class AbsractElectroDevice
{
private:
    std::string name = "No name";
    double power;
    bool isPlugged;

public:
    void PlugIn();
    void PlugOut();
    double GetPowerConsumotion();
    std::string getName();
};

