#include "gpu.hpp"
#include <array>
#include <cstdio>
#include <string>

namespace Toollibs::Platform::Linux::GPU
{
    std::string GetName()
    {
        std::array<char, 256> buffer;
        std::string result;

        FILE* pipe = popen("lspci | grep -i vga", "r");

        if (!pipe)
            return "Unknown GPU";

        while (fgets(buffer.data(), buffer.size(), pipe))
            result += buffer.data();

        pclose(pipe);

        if (result.empty())
            return "Unknown GPU";

        return result;
    }

    std::string GetDriver()
    {
        std::array<char, 256> buffer;
        std::string result;

        FILE* pipe = popen("lspci -k | grep -A 3 -i vga", "r");

        if (!pipe)
            return "Unknown Driver";

        while (fgets(buffer.data(), buffer.size(), pipe))
            result += buffer.data();

        pclose(pipe);

        return result.empty() ? "Unknown Driver" : result;
    }
}
