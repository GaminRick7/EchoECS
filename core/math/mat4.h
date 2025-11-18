#pragma once

struct Mat4 {
    float m[16];

    static Mat4 identity();
    static Mat4 translation(const Vec3&);
    static Mat4 scale(const Vec3&);
    static Mat4 rotationX(float);
    static Mat4 rotationY(float);
    static Mat4 rotationZ(float);
    static Mat4 perspective(float fov, float aspect, float near, float far);
    static Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up);

    Mat4 operator*(const Mat4&) const;
    Vec3 operator*(const Vec3&) const;

    Mat4 transpose() const;
    Mat4 inverse() const;

    float* data() { return m; }
    const float* data() const { return m; }
};