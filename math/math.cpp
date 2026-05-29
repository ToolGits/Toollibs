#include "math.hpp"
#include <cmath>

namespace Toollibs::Math {

Vec2 Add(const Vec2& a, const Vec2& b) {
    return {a.x + b.x, a.y + b.y};
}

Vec2 Sub(const Vec2& a, const Vec2& b) {
    return {a.x - b.x, a.y - b.y};
}

Vec2 Scale(const Vec2& v, float s) {
    return {v.x * s, v.y * s};
}

float Length(const Vec2& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

float Distance(const Vec2& a, const Vec2& b) {
    return Length(Sub(a, b));
}

}
