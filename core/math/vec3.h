#pragma once
#include <valarray>

namespace math
{
    struct Vec3
    {
        float x, y, z;
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

        Vec3 operator+(const Vec3& o) const{ return {x + o.x, y + o.y, z + o.z}; }
        Vec3 operator-(const Vec3& o) const{ return {x - o.x, y - o.y, z - o.z}; }
        Vec3 operator*(float o) const{ return {x * o, y * o, z * o}; }

        float dot(const Vec3& o) const{ return x * o.x + y * o.y + z * o.z; }
        Vec3 cross(const Vec3& o) const
        {
            return {y * o.z - z * o.y,
                    z * o.x - x * o.z,
                    x * o.y - y * o.x};
        }
        float length() const{ return std::sqrt(x * x + y * y + z * z); }

        Vec3 normalized() const{
            float len = length();
            return len > 0 ? (*this) * (1.0f/len) : *this;
        }
    };
}
