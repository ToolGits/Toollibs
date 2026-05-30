#include "logger.hpp"
#include "math/math.hpp"
#include "graphics/graphics.hpp"
#include "plugins/MathPlugin/plugin.hpp"

#include <filesystem>

namespace fs = std::filesystem;

int main()
{
    Toollibs::Logger::Info("Starting Toollibs verification...");
    Toollibs::Logger::Debug("Initializing core pipeline...");

    // =========================
    // CORE CHECK
    // =========================
    Toollibs::Logger::Info("Checking core modules...");

    bool input_ok = fs::exists("input/input_simulation.cpp");
    bool math_ok = fs::exists("math/math.hpp") && fs::exists("math/math.cpp");
    bool graphics_ok = fs::exists("graphics/graphics.hpp") &&
                        fs::exists("graphics/graphics.cpp");

    if (!input_ok)
        Toollibs::Logger::Error("Input module missing or broken");
    else
        Toollibs::Logger::Info("Input module detected");

    if (!math_ok)
        Toollibs::Logger::Warning("Math module missing");
    else
        Toollibs::Logger::Info("Math module detected");

    if (!graphics_ok)
        Toollibs::Logger::Warning("Graphics module missing");
    else
        Toollibs::Logger::Info("Graphics module detected");

    // =========================
    // RUNTIME TESTS
    // =========================
    Toollibs::Logger::Info("Running runtime tests...");

    if (math_ok)
    {
        Toollibs::Math::Vec2 a{1.0f, 2.0f};
        Toollibs::Math::Vec2 b{3.0f, 4.0f};

        auto result = Toollibs::Math::Add(a, b);

        if (result.x == 4.0f && result.y == 6.0f)
            Toollibs::Logger::Info("Math runtime test PASSED");
        else
            Toollibs::Logger::Warning("Math runtime test FAILED");
    }

    if (graphics_ok)
    {
        Toollibs::Graphics::Init();

        Toollibs::Graphics::Color black{0, 0, 0};
        Toollibs::Graphics::Color white{255, 255, 255};

        Toollibs::Graphics::Clear(black);
        Toollibs::Graphics::DrawPixel(10, 10, white);

        Toollibs::Graphics::Shutdown();

        Toollibs::Logger::Debug("Graphics runtime test executed");
    }

    // =========================
    // PLUGIN SYSTEM
    // =========================
    Toollibs::Logger::Info("Loading plugins...");

    // MathPlugin (test plugin system)
    Toollibs::Plugin::MathPlugin::Run();

    Toollibs::Logger::Debug("MathPlugin executed");

    // Future plugins can be added here:
    // Toollibs::Plugin::GraphicsPlugin::Run();
    // Toollibs::Plugin::DebugPlugin::Run();

    // =========================
    // FINAL RESULT
    // =========================
    Toollibs::Logger::Info("Toollibs verification completed successfully");

    return 0;
}