#pragma once
#include <valarray>

namespace math
{
    struct Vec2
    {
        float x, y;
        Vec2(float x, float y) : x(x), y(y) {}

        Vec2 operator+(const Vec2& o) const{ return {x + o.x, y + o.y}; }
        Vec2 operator-(const Vec2& o) const{ return {x - o.x, y - o.y}; }
        Vec2 operator*(float o) const{ return {x * o, y * o}; }

        float dot(const Vec2& o) const{ return x * o.x + y * o.y; }

        float length() const{ return std::sqrt(x * x + y * y); }

        Vec2 normalized() const{
            float len = length();
            return len > 0 ? (*this) * (1.0f/len) : *this;
        }
    };
}
