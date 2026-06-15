#include "font_renderer.hpp"

#include <iostream>

int main(int argc, char** argv) {

    if (argc < 2) {

        std::cout
            << "Usage:\n"
            << "font_preview <font.ttf>\n";

        return 1;
    }

    std::string font_path = argv[1];

    std::string output =
        "font-preview.png";

    toollibs::FontRenderer renderer;

    if (!renderer.render_preview(
        font_path,
        output
    )) {

        return 1;
    }

    std::cout
        << "Generated: "
        << output
        << "\n";

    return 0;
}