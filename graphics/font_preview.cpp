#include "font_renderer.hpp"

#include <iostream>

int main(
    int argc,
    char** argv
) {

    if (argc < 2) {

        std::cout
            << "Usage:\n"
            << "font_preview <font.ttf>\n";

        return 1;
    }

    toollibs::FontRenderer renderer;

    if (
        !renderer.render_preview(
            argv[1],
            "preview.png"
        )
    ) {

        return 1;
    }

    std::cout
        << "Generated preview.png\n";

    return 0;
}