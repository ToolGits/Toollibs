#include <iostream>

#include "battery.hpp"

using namespace Toollibs::Platform::Android;

int main()
{
    std::cout
        << "=== TOOLLIBS BATTERY INFO ===\n\n";

    if (!Battery::IsAvailable())
    {
        std::cout
            << "Battery: Not Available\n";

        return 0;
    }

    std::cout
        << "Battery     : "
        << Battery::GetPercentage()
        << "%\n";

    std::cout
        << "Status      : "
        << Battery::GetStatus()
        << "\n";

    std::cout
        << "Health      : "
        << Battery::GetHealth()
        << "\n";

    std::cout
        << "Technology  : "
        << Battery::GetTechnology()
        << "\n";

    std::cout
        << "Voltage     : "
        << Battery::GetVoltage()
        << " V\n";

    std::cout
        << "Temperature : "
        << Battery::GetTemperature()
        << " °C\n";

    return 0;
}