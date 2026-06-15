#pragma once

#include <string>

namespace toollibs {

class FontRenderer {
public:
    bool render_preview(
        const std::string& font_path,
        const std::string& output_png
    );
};

}