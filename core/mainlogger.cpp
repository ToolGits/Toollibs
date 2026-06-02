#include "logger.hpp"

#include "math/math.hpp"
#include "graphics/graphics.hpp"
#include "plugins/MathPlugin/plugin.hpp"

#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

namespace Toollibs {

bool FileValid(const std::string& path)
{
    return fs::exists(path) && fs::file_size(path) > 0;
}

struct ModuleStatus
{
    std::string name;
    bool ok;
};

void RunMathTests()
{
    Logger::Info("Running Math tests...");

    Toollibs::Math::Vec2 a{1.0f, 2.0f};
    Toollibs::Math::Vec2 b{3.0f, 4.0f};

    auto result = Toollibs::Math::Add(a, b);

    if (result.x == 4.0f && result.y == 6.0f)
        Logger::Info("Math: Vec2 Add test PASSED");
    else
        Logger::Error("Math: Vec2 Add test FAILED");
}

void RunGraphicsTests()
{
    Logger::Info("Running Graphics tests...");

    Toollibs::Graphics::Init();

    Toollibs::Graphics::Color black{0, 0, 0};
    Toollibs::Graphics::Color white{255, 255, 255};

    Toollibs::Graphics::Clear(black);
    Toollibs::Graphics::DrawPixel(10, 10, white);

    Toollibs::Graphics::Shutdown();

    Logger::Info("Graphics: pipeline executed successfully");
}

void RunPluginTests()
{
    Logger::Info("Running Plugin system tests...");

    try
    {
        Toollibs::Plugin::MathPlugin::Run();
        Logger::Info("Plugin: MathPlugin executed successfully");
    }
    catch (const std::exception& e)
    {
        Logger::Error(std::string("Plugin system error: ") + e.what());
    }
    catch (...)
    {
        Logger::Error("Plugin system unknown error occurred");
    }
}

}

int main()
{
    using namespace Toollibs;

    Logger::Info("======================================");
    Logger::Info("Toollibs Verification Pipeline Start");
    Logger::Info("======================================");

    // =========================
    // MODULE CHECKS
    // =========================
    std::vector<ModuleStatus> modules =
    {
        {"Input", FileValid("input/input_simulation.cpp")},
        {"Math", FileValid("math/math.hpp") && FileValid("math/math.cpp")},
        {"Graphics", FileValid("graphics/graphics.hpp") && FileValid("graphics/graphics.cpp")},
        {"Plugins", FileValid("plugins/MathPlugin/plugin.hpp")}
    };

    Logger::Info("Checking module integrity...");

    int okModules = 0;

    for (const auto& m : modules)
    {
        if (m.ok)
        {
            Logger::Info(m.name + " module OK");
            okModules++;
        }
        else
        {
            Logger::Error(m.name + " module MISSING or INVALID");
        }
    }

    Logger::Info("Modules OK: " + std::to_string(okModules) + "/" + std::to_string(modules.size()));

    // =========================
    // RUNTIME TESTS
    // =========================
    Logger::Info("Starting runtime validation...");

    if (modules[1].ok)
        RunMathTests();

    if (modules[2].ok)
        RunGraphicsTests();

    // =========================
    // PLUGINS
    // =========================
    if (modules[3].ok)
        RunPluginTests();

    // =========================
    // FINAL REPORT
    // =========================
    Logger::Info("======================================");
    Logger::Info("Toollibs Verification Completed");
    Logger::Info("======================================");

    if (okModules == modules.size())
        Logger::Info("SYSTEM STATUS: HEALTHY");
    else
        Logger::Warning("SYSTEM STATUS: DEGRADED");

    return (okModules == modules.size()) ? 0 : 1;
}