#include "plugin.hpp"
#include "../../core/logger.hpp"
#include "../../math/math.hpp"

namespace Toollibs::Plugin {

    void MathPlugin::Run()
    {
        Toollibs::Logger::Info("MathPlugin started...");

        float a = 10.0f;
        float b = 5.0f;

        Toollibs::Math::Vec2 add = Toollibs::Math::Add(a, b);
Toollibs::Math::Vec2 sub = Toollibs::Math::Sub(a, b);
Toollibs::Math::Vec2 scale = Toollibs::Math::Scale(a, 2.0f);

        Toollibs::Logger::Debug("Add test executed");
        Toollibs::Logger::Debug("Sub test executed");
        Toollibs::Logger::Debug("Scale test executed");

        Toollibs::Logger::Info("MathPlugin finished successfully");
    }

}
