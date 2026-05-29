#include "logger.hpp"
#include "math/math.hpp"
#include "graphics/graphics.hpp"

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

        Toollibs::Math::Add(a, b);

        Toollibs::Logger::Debug("Math module runtime test executed");
    }
    else
    {
        Toollibs::Logger::Warning("Math module incomplete or missing");
    }

// =========================
// Graphics module check
// =========================
if (!fs::exists("graphics/graphics.hpp") ||
    !fs::exists("graphics/graphics.cpp"))
{
    Toollibs::Logger::Warning("Graphics module incomplete or missing");
}
else
{
    Toollibs::Logger::Info("Graphics module detected");

    Toollibs::Graphics::Init();

    Toollibs::Graphics::Color black{0, 0, 0};
    Toollibs::Graphics::Color white{255, 255, 255};

    Toollibs::Graphics::Clear(black);
    Toollibs::Graphics::DrawPixel(10, 10, white);

    Toollibs::Graphics::Shutdown();

    Toollibs::Logger::Debug("Graphics module runtime test executed");
}


    Toollibs::Logger::Info("Toollibs verification completed successfully");

    return 0;
}
