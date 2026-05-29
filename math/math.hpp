#pragma once

namespace Toollibs::Math {

// =====================
// Vec2
// =====================
struct Vec2 {
    float x;
    float y;
};

Vec2 Add(const Vec2& a, const Vec2& b);
Vec2 Sub(const Vec2& a, const Vec2& b);
Vec2 Scale(const Vec2& v, float s);

float Length(const Vec2& v);
float Distance(const Vec2& a, const Vec2& b);

}
