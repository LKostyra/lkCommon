#pragma once
#define _LKCOMMON_MATH_VECTOR4_HPP_

#include <xmmintrin.h>
#include "lkCommon/lkCommon.hpp"


namespace lkCommon {
namespace Math {

class LKCOMMON_ALIGN(16) Vector4 final
{
    union Vector4f
    {
        __m128 m;
        float f[4];

        LKCOMMON_INLINE Vector4f()
            : m(_mm_setzero_ps())
        {}

        LKCOMMON_INLINE Vector4f(const __m128& m)
            : m(m)
        {}
    } mValue;

public:
    Vector4();
    Vector4(const float x);
    Vector4(const float x, const float y, const float z, const float w);
    Vector4(const float* v);
    Vector4(const __m128& v);
    Vector4(const Vector4& other);
    Vector4(Vector4&& other);
    Vector4& operator=(const Vector4& other);
    Vector4& operator=(Vector4&& other);
    ~Vector4() = default;

    const float* Data() const;
    float Length() const;
    Vector4 Normalize() const;

    // Access operator
    float& operator[](const size_t index);
    float operator[](const size_t index) const;

    // Addition
    Vector4& operator+=(const Vector4& other);
    Vector4& operator+=(const float value);
    Vector4 operator+(const Vector4& other) const;
    Vector4 operator+(const float value) const;

    // Subtraction
    Vector4& operator-=(const Vector4& other);
    Vector4& operator-=(const float value);
    Vector4 operator-(const Vector4& other) const;
    Vector4 operator-(const float value) const;

    // Multiplication
    Vector4& operator*=(const Vector4& other);
    Vector4& operator*=(const float value);
    Vector4 operator*(const Vector4& other) const;
    Vector4 operator*(const float value) const;

    // Division
    Vector4& operator/=(const Vector4& other);
    Vector4& operator/=(const float value);
    Vector4 operator/(const Vector4& other) const;
    Vector4 operator/(const float value) const;

    // Products
    float Dot(const Vector4& other) const;
    Vector4 Cross(const Vector4& other) const;

    // Comparison
    bool operator==(const Vector4& other) const;
    bool operator!=(const Vector4& other) const;

    // Friendships
    friend std::ostream& operator<<(std::ostream& os, const Vector4& v);
};

} // namespace Math
} // namespace lkCommon

#include "Vector4Impl.hpp"
