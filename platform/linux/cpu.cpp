#include "cpu.hpp"
#include <fstream>
#include <string>
#include <unistd.h>

namespace Toollibs::Platform::Linux::CPU
{
    std::string GetName()
    {
        std::ifstream file("/proc/cpuinfo");
        std::string line;

        while (std::getline(file, line))
        {
            if (line.find("model name") != std::string::npos)
                return line.substr(line.find(":") + 2);
        }

        return "Unknown CPU";
    }

    std::string GetVendor()
    {
        std::ifstream file("/proc/cpuinfo");
        std::string line;

        while (std::getline(file, line))
        {
            if (line.find("vendor_id") != std::string::npos)
                return line.substr(line.find(":") + 2);
        }

        return "Unknown Vendor";
    }

    int GetCores()
    {
        return sysconf(_SC_NPROCESSORS_ONLN);
    }
}
