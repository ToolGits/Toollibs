#include "battery.hpp"

#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

namespace Toollibs::Platform::Android::Battery
{
    static fs::path FindBatteryPath()
    {
        fs::path root("/sys/class/power_supply");

        if (!fs::exists(root))
            return {};

        for (const auto& entry : fs::directory_iterator(root))
        {
            if (!entry.is_directory())
                continue;

            if (fs::exists(entry.path() / "capacity"))
                return entry.path();
        }

        return {};
    }

    static std::string ReadString(const fs::path& file)
    {
        std::ifstream stream(file);

        if (!stream)
            return "Unknown";

        std::string value;
        std::getline(stream, value);

        return value.empty() ? "Unknown" : value;
    }

    static long long ReadNumber(const fs::path& file)
    {
        std::ifstream stream(file);

        if (!stream)
            return -1;

        long long value = -1;
        stream >> value;

        return value;
    }

    bool IsAvailable()
    {
        return !FindBatteryPath().empty();
    }

    int GetPercentage()
    {
        auto battery = FindBatteryPath();

        if (battery.empty())
            return -1;

        return static_cast<int>(
            ReadNumber(battery / "capacity")
        );
    }

    std::string GetStatus()
    {
        auto battery = FindBatteryPath();

        if (battery.empty())
            return "Unknown";

        return ReadString(
            battery / "status"
        );
    }

    std::string GetHealth()
    {
        auto battery = FindBatteryPath();

        if (battery.empty())
            return "Unknown";

        return ReadString(
            battery / "health"
        );
    }

    std::string GetTechnology()
    {
        auto battery = FindBatteryPath();

        if (battery.empty())
            return "Unknown";

        return ReadString(
            battery / "technology"
        );
    }

    double GetVoltage()
    {
        auto battery = FindBatteryPath();

        if (battery.empty())
            return -1.0;

        long long voltage =
            ReadNumber(battery / "voltage_now");

        if (voltage < 0)
            return -1.0;

        return voltage / 1000000.0;
    }

    double GetTemperature()
    {
        auto battery = FindBatteryPath();

        if (battery.empty())
            return -1.0;

        long long temp =
            ReadNumber(battery / "temp");

        if (temp < 0)
            return -1.0;

        return temp / 10.0;
    }
}