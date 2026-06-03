#pragma once

#include <string>

namespace Toollibs::Platform::Linux::CPU
{
    std::string GetName();
    std::string GetVendor();

    int GetCores();
    int GetThreads();
}