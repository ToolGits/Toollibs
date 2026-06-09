#pragma once

#include <string>

namespace Toollibs::Platform::Android::Battery
{
    bool IsAvailable();

    int GetPercentage();

    std::string GetStatus();

    std::string GetHealth();

    std::string GetTechnology();

    double GetVoltage();

    double GetTemperature();
}