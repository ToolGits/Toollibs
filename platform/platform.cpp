#include "platform.hpp"

#if defined(_WIN32)
    #define TOOLLIBS_WINDOWS
#elif defined(__linux__)
    #define TOOLLIBS_LINUX
#endif

namespace Toollibs {

    Platform GetPlatform()
    {
    #ifdef TOOLLIBS_WINDOWS
        return Platform::Windows;
    #elif defined(TOOLLIBS_LINUX)
        return Platform::Linux;
    #else
        return Platform::Unknown;
    #endif
    }

}