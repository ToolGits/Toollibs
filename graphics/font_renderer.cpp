#include "font_renderer.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include <iostream>
#include <vector>

namespace toollibs {

bool FontRenderer::render_preview(
    const std::string& font_path,
    const std::string& output_png
) {

    FT_Library library;

    if (FT_Init_FreeType(&library)) {
        std::cerr << "Failed to initialize FreeType\n";
        return false;
    }

    FT_Face face;

    if (FT_New_Face(
        library,
        font_path.c_str(),
        0,
        &face
    )) {

        std::cerr << "Failed to load font\n";

        FT_Done_FreeType(library);

        return false;
    }

    FT_Set_Pixel_Sizes(
        face,
        0,
        32
    );

    // PNG generation will go here

    FT_Done_Face(face);
    FT_Done_FreeType(library);

    return true;
}

}