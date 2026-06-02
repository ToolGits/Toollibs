#include "logger.hpp"

#include "math/math.hpp"
#include "graphics/graphics.hpp"
#include "plugins/MathPlugin/plugin.hpp"

#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace Toollibs {

// =========================
// SAFE FILE CHECK
// =========================
bool FileValid(const std::string& path)
{
    try
    {
        return fs::exists(path) &&
               fs::is_regular_file(path) &&
               fs::file_size(path) > 0;
    }
    catch (...)
    {
        return false;
    }
}

// =========================
// MODULE STRUCT
// =========================
struct Module
{
    std::string name;
    std::string path;
    bool ok;
};

// =========================
// MATH TEST
// =========================
void RunMathTests()
{
    Logger::Info("Running Math tests...");

    Math::Vec2 a{1.0f, 2.0f};
    Math::Vec2 b{3.0f, 4.0f};

    auto result = Math::Add(a, b);

    if (result.x == 4.0f && result.y == 6.0f)
        Logger::Info("Math: Vec2 Add test PASSED");
    else
        Logger::Error("Math: Vec2 Add test FAILED");
}

// =========================
// GRAPHICS TEST
// =========================
void RunGraphicsTests()
{
    Logger::Info("Running Graphics tests...");

    Graphics::Init();

    Graphics::Color black{0, 0, 0};
    Graphics::Color white{255, 255, 255};

    Graphics::Clear(black);
    Graphics::DrawPixel(10, 10, white);

    Graphics::Shutdown();

    Logger::Info("Graphics: pipeline executed successfully");
}

// =========================
// PLUGIN TEST
// =========================
void RunPluginTests()
{
    Logger::Info("Running Plugin system tests...");

    try
    {
        Plugin::MathPlugin::Run();
        Logger::Info("Plugin: MathPlugin executed successfully");
    }
    catch (const std::exception& e)
    {
        Logger::Error(std::string("Plugin error: ") + e.what());
    }
    catch (...)
    {
        Logger::Error("Plugin unknown error occurred");
    }
}

// =========================
// STATUS REPORT
// =========================
void PrintStatus(int ok, int total)
{
    Logger::Info("======================================");
    Logger::Info("Toollibs Verification Completed");
    Logger::Info("======================================");

    if (ok == total)
        Logger::Info("SYSTEM STATUS: HEALTHY");
    else if (ok > 0)
        Logger::Warning("SYSTEM STATUS: DEGRADED");
    else
        Logger::Error("SYSTEM STATUS: CRITICAL FAILURE");
}

} // namespace Toollibs

// =========================
// MAIN
// =========================
int main()
{
    using namespace Toollibs;

    Logger::Info("======================================");
    Logger::Info("Toollibs Verification Pipeline Start");
    Logger::Info("======================================");

    // =========================
    // MODULE LIST
    // =========================
    std::vector<Module> modules =
    {
        {"Input", "input/input_simulation.cpp", false},
        {"Math", "math/math.hpp", false},
        {"Graphics", "graphics/graphics.hpp", false},
        {"Plugins", "plugins/MathPlugin/plugin.hpp", false}
    };

    Logger::Info("Checking module integrity...");

    int okModules = 0;

    for (auto& m : modules)
    {
        m.ok = FileValid(m.path);

        if (m.ok)
        {
            Logger::Info(m.name + " module OK");
            ++okModules;
        }
        else
        {
            Logger::Error(m.name + " module MISSING or INVALID");
        }
    }

    Logger::Info("Modules OK: " +
                 std::to_string(okModules) + "/" +
                 std::to_string(modules.size()));

    // =========================
    // RUNTIME TESTS
    // =========================
    Logger::Info("Starting runtime validation...");

    const bool mathOk = modules[1].ok;
    const bool graphicsOk = modules[2].ok;
    const bool pluginOk = modules[3].ok;

    if (mathOk)
        RunMathTests();

    if (graphicsOk)
        RunGraphicsTests();

    if (pluginOk)
        RunPluginTests();

    // =========================
    // FINAL STATUS
    // =========================
    PrintStatus(okModules, static_cast<int>(modules.size()));

    return (okModules == static_cast<int>(modules.size())) ? 0 : 1;
}