#pragma once
#include "vec3.h"
#include "vec4.h"

namespace math
{
    struct Mat4 {
        float m[16];

        static Mat4 identity()
        {
            Mat4 r{};
            r.m[0] = r.m[5] = r.m[10] = r.m[15] = 1.0f;
            return r;
        }

        static Mat4 translation(const math::Vec3& v)
        {
            Mat4 r = identity();
            r.m[12] = v.x;
            r.m[13] = v.y;
            r.m[14] = v.z;

            return r;
        }

        static Mat4 scale(const math::Vec3& v)
        {
            Mat4 r{};
            r.m[0]  = v.x;
            r.m[5]  = v.y;
            r.m[10] = v.z;
            r.m[15] = 1.0f;
            return r;
        }

        //TODO: finsih rotational
        static Mat4 rotationX(float);
        static Mat4 rotationY(float);
        static Mat4 rotationZ(float);

        static Mat4 perspective(float fovX, float aspectRatio, float near, float far)
        {
            const float DEG2RAD = std::acos(-1.0f) / 180;

            float tangent = std::tan(fovX/2 * DEG2RAD);
            float right = near * tangent;
            float top = right / aspectRatio;

            Mat4 r{};
            r[0]  =  near / right;
            r[5]  =  near / top;
            r[10] = -(far + near) / (far - near);
            r[11] = -1;
            r[14] = -(2 * far * near) / (far - near);
            r[15] =  0;
            return r;
        }
        //TODO: finish lookAT
        static Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up);

        float& operator[](size_t i)
        {
            if (i >= 16)
                throw std::out_of_range("Mat4 index out of range");
            return m[i];
        }

        const float& operator[](size_t i) const
        {
            if (i >= 16)
                throw std::out_of_range("Mat4 index out of range");
            return m[i];
        }

        Mat4 Mat4::operator*(const Mat4& b) const {
            Mat4 r{};
            for (int row = 0; row < 4; ++row) {
                for (int col = 0; col < 4; ++col) {
                    r.m[col*4 + row] =
                        m[0*4 + row] * b.m[col*4 + 0] +
                        m[1*4 + row] * b.m[col*4 + 1] +
                        m[2*4 + row] * b.m[col*4 + 2] +
                        m[3*4 + row] * b.m[col*4 + 3];
                }
            }
            return r;
        }

        Vec4 Mat4::operator*(const Vec4& v) const {
            return {
                m[0] * v.x + m[4] * v.y + m[8]  * v.z + m[12] * v.w,
                m[1] * v.x + m[5] * v.y + m[9]  * v.z + m[13] * v.w,
                m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14] * v.w,
                m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15] * v.w
            };
        }

        Mat4 Mat4::transpose() const {
            Mat4 r{};
            for (int row = 0; row < 4; ++row) {
                for (int col = 0; col < 4; ++col) {
                    r.m[col * 4 + row] = m[row * 4 + col];
                }
            }

            return r;
        }

        // Mat4 inverse() const;

        float* data() { return m; }
        const float* data() const { return m; }
    };
}
