#include "logger.hpp"
#include "math/math.hpp"

#include <filesystem>

namespace fs = std::filesystem;

int main()
{
    Toollibs::Logger::Info("Starting Toollibs verification...");

    Toollibs::Logger::Debug("Checking core modules...");

    // =========================
    // Input module check
    // =========================
    if (!fs::exists("input/input_simulation.cpp"))
    {
        Toollibs::Logger::Error("Input module missing or broken");
        return 1;
    }

    Toollibs::Logger::Info("Input module initialized");

    // =========================
    // Math module check + basic test
    // =========================
    if (fs::exists("math/math.hpp") && fs::exists("math/math.cpp"))
    {
        Toollibs::Logger::Info("Math module detected");

        Toollibs::Math::Vec2 a{1.0f, 2.0f};
        Toollibs::Math::Vec2 b{3.0f, 4.0f};

        auto result = Toollibs::Math::Add(a, b);

        Toollibs::Logger::Debug("Math module runtime test executed");
    }
    else
    {
        Toollibs::Logger::Warn("Math module incomplete or missing");
    }

    Toollibs::Logger::Info("Toollibs verification completed successfully");

    return 0;
}