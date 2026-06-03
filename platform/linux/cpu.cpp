#include "cpu.hpp"

#include <fstream>
#include <string>
#include <unistd.h>
#include <thread>

namespace Toollibs::Platform::Linux::CPU
{
    static std::string GetCpuInfoValue(const std::string& key)
    {
        std::ifstream file("/proc/cpuinfo");
        std::string line;

        if (!file.is_open())
            return "Unknown";

        while (std::getline(file, line))
        {
            if (line.rfind(key, 0) == 0)
            {
                size_t pos = line.find(':');
                if (pos != std::string::npos)
                    return line.substr(pos + 2);
            }
        }

        return "Unknown";
    }

    std::string GetName()
    {
        return GetCpuInfoValue("model name");
    }

    std::string GetVendor()
    {
        return GetCpuInfoValue("vendor_id");
    }

    int GetCores()
    {
        long cores = sysconf(_SC_NPROCESSORS_ONLN);
        return (cores > 0) ? static_cast<int>(cores) : 1;
    }

    int GetThreads()
    {
        auto t = std::thread::hardware_concurrency();
        return (t > 0) ? static_cast<int>(t) : GetCores();
    }
}