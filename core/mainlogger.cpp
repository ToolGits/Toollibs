#include "logger.hpp"

#include <filesystem>

namespace fs = std::filesystem;

int main()
{
    Toollibs::Logger::Info("Starting Toollibs...");

    if (!fs::exists("../input"))
    {
        Toollibs::Logger::Error("Input module verification failed");
        return 1;
    }

    if (!fs::exists("../input/input_simulation.cpp"))
    {
        Toollibs::Logger::Error("Input module verification failed");
        return 1;
    }

    Toollibs::Logger::Info("Input module initialized");

    Toollibs::Logger::Info("Toollibs initialized successfully");

    return 0;
}
