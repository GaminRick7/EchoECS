#pragma once
#include <valarray>

namespace math
{
    struct Vec4
    {
        float x, y, z, w;
        Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        Vec4 operator+(const Vec4& o) const{ return {x + o.x, y + o.y, z + o.z, w + o.w}; }
        Vec4 operator-(const Vec4& o) const{ return {x - o.x, y - o.y, z - o.z, w - o.w}; }
        Vec4 operator*(float o) const{ return {x * o, y * o, z * o, w * o}; }
        float& operator[](int i)
        {

        };

        float dot(const Vec4& o) const{ return x * o.x + y * o.y + z * o.z + w * o.w; }

        float length() const{ return std::sqrt(x * x + y * y + z * z + w * w); }

        Vec4 normalized() const{
            float len = length();
            return len > 0 ? (*this) * (1.0f/len) : *this;
        }
    };
}
