#include "font_renderer.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include <vector>
#include <iostream>

namespace toollibs {

bool FontRenderer::render_preview(
    const std::string& font_path,
    const std::string& output_png
) {

    FT_Library library;

    if (FT_Init_FreeType(&library)) {
        std::cerr << "FreeType init failed\n";
        return false;
    }

    FT_Face face;

    if (FT_New_Face(
        library,
        font_path.c_str(),
        0,
        &face
    )) {

        std::cerr << "Could not load font\n";

        FT_Done_FreeType(library);

        return false;
    }

    FT_Set_Pixel_Sizes(
        face,
        0,
        48
    );

    const int WIDTH = 1200;
    const int HEIGHT = 300;

    std::vector<unsigned char> image(
        WIDTH * HEIGHT * 4,
        255
    );

    const std::string text =
        "Toollibs FontsFirst";

    int pen_x = 50;
    int pen_y = 120;

    for (char c : text) {

        if (
            FT_Load_Char(
                face,
                c,
                FT_LOAD_RENDER
            )
        ) {
            continue;
        }

        FT_GlyphSlot glyph =
            face->glyph;

        FT_Bitmap& bitmap =
            glyph->bitmap;

        for (
            int row = 0;
            row < bitmap.rows;
            row++
        ) {

            for (
                int col = 0;
                col < bitmap.width;
                col++
            ) {

                int x =
                    pen_x +
                    glyph->bitmap_left +
                    col;

                int y =
                    pen_y -
                    glyph->bitmap_top +
                    row;

                if (
                    x < 0 ||
                    y < 0 ||
                    x >= WIDTH ||
                    y >= HEIGHT
                ) {
                    continue;
                }

                unsigned char value =
                    bitmap.buffer[
                        row * bitmap.pitch +
                        col
                    ];

                int pixel =
                    (y * WIDTH + x) * 4;

                image[pixel + 0] = 0;
                image[pixel + 1] = 0;
                image[pixel + 2] = 0;
                image[pixel + 3] = value;
            }
        }

        pen_x +=
            glyph->advance.x >> 6;
    }

    stbi_write_png(
        output_png.c_str(),
        WIDTH,
        HEIGHT,
        4,
        image.data(),
        WIDTH * 4
    );

    FT_Done_Face(face);
    FT_Done_FreeType(library);

    return true;
}

}