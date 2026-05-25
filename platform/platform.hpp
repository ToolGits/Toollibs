#pragma once

namespace Toollibs {

    enum class Platform {
        Linux,
        Windows,
        Unknown
    };

    Platform GetPlatform();

}