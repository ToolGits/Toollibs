#include "plugin.hpp"

#include "core/logger.hpp"
#include "math/math.hpp"

namespace Toollibs::Plugin {

void MathPlugin::Run()
{
    Toollibs::Logger::Info("================================");
    Toollibs::Logger::Info("MathPlugin started");
    Toollibs::Logger::Info("================================");

    Toollibs::Math::Vec2 a{10.0f, 5.0f};
    Toollibs::Math::Vec2 b{3.0f, 2.0f};

    auto add = Toollibs::Math::Add(a, b);
    auto sub = Toollibs::Math::Sub(a, b);
    auto scale = Toollibs::Math::Scale(a, 2.0f);

    // =========================
    // VALIDATION
    // =========================
    if (add.x == 13.0f && add.y == 7.0f)
        Toollibs::Logger::Debug("Add operation OK");
    else
        Toollibs::Logger::Error("Add operation FAILED");

    if (sub.x == 7.0f && sub.y == 3.0f)
        Toollibs::Logger::Debug("Sub operation OK");
    else
        Toollibs::Logger::Error("Sub operation FAILED");

    if (scale.x == 20.0f && scale.y == 10.0f)
        Toollibs::Logger::Debug("Scale operation OK");
    else
        Toollibs::Logger::Error("Scale operation FAILED");

    Toollibs::Logger::Info("================================");
    Toollibs::Logger::Info("MathPlugin finished successfully");
    Toollibs::Logger::Info("================================");
}

} // namespace Toollibs::Plugin