#include "plugin.hpp"
#include "../../core/logger.hpp"
#include "../../math/math.hpp"

namespace Toollibs::Plugin {

    void MathPlugin::Run()
    {
        Toollibs::Logger::Info("MathPlugin started...");

        Toollibs::Math::Vec2 a{10.0f, 5.0f};
        Toollibs::Math::Vec2 b{3.0f, 2.0f};

        auto add = Toollibs::Math::Add(a, b);
        auto sub = Toollibs::Math::Sub(a, b);
        auto scale = Toollibs::Math::Scale(a, 2.0f);

        Toollibs::Logger::Debug("Add operation executed");
        Toollibs::Logger::Debug("Sub operation executed");
        Toollibs::Logger::Debug("Scale operation executed");

        Toollibs::Logger::Info("MathPlugin finished successfully");
    }

}
