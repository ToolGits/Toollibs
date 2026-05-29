#include "graphics.hpp"
#include <iostream>

namespace Toollibs::Graphics {

void Init()
{
    std::cout << "[Graphics] Initialized\n";
}

void Clear(Color color)
{
    std::cout << "[Graphics] Clear screen RGB("
              << color.r << "," << color.g << "," << color.b << ")\n";
}

void DrawPixel(int x, int y, Color color)
{
    std::cout << "[Graphics] Pixel at ("
              << x << "," << y << ") RGB("
              << color.r << "," << color.g << "," << color.b << ")\n";
}

void Shutdown()
{
    std::cout << "[Graphics] Shutdown\n";
}

}
