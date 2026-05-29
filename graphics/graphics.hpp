#pragma once

namespace Toollibs::Graphics {

struct Color {
    int r, g, b;
};

struct Pixel {
    int x, y;
    Color color;
};

void Init();
void Clear(Color color);
void DrawPixel(int x, int y, Color color);
void Shutdown();

}
