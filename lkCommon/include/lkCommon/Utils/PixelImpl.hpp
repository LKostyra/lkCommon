/**
 * @file
 * @author LKostyra (costyrra.xl@gmail.com)
 * @brief  Pixel utility template class implementation.
 */

#pragma once

#include "Pixel.hpp"


namespace {


// value range clamps per type (ex. limits float to 0.0f - 1.0f range)
template <typename T>
LKCOMMON_INLINE T Clamp(T x)
{
    staic_assert(std::is_same<uint8_t, typename std::remove_cv<T>::type>::value
              || std::is_same<float, typename std::remove_cv<T>::type>::value,
              "Incompatible type provided for clamping");
}

template <>
LKCOMMON_INLINE uint8_t Clamp(uint8_t x)
{
    return x;
}

template <>
LKCOMMON_INLINE float Clamp(float x)
{
    x = (x > 1.0f ? 1.0f : x);
    return (x < 0.0f ? 0.0f : x);
}


// converters

template <typename Src, typename Dst>
LKCOMMON_INLINE Dst ConvertColor(Src source)
{
    static_assert(std::is_same<uint8_t, typename std::remove_cv<Src>::type>::value
               || std::is_same<float, typename std::remove_cv<Src>::type>::value,
               "Incompatible types provided for conversion");
}

template <>
LKCOMMON_INLINE uint8_t ConvertColor(float source)
{
    return static_cast<uint8_t>(Clamp(source) * 255);
}

template <>
LKCOMMON_INLINE float ConvertColor(uint8_t source)
{
    return static_cast<float>(Clamp(source)) / 255.0f;
}


} // namespace


namespace lkCommon {
namespace Utils {

// generic constructors

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>::Pixel()
    : mColors{static_cast<T>(0)}
{
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>::Pixel(T color)
{
    color = Clamp(color);
    for (size_t i = 0; i < ComponentCount; ++i)
        mColors[i] = color;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>::Pixel(const T colors[ComponentCount])
{
    for (size_t i = 0; i < ComponentCount; ++i)
        mColors[i] = Clamp(colors[i]);
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>::Pixel(std::initializer_list<T> l)
    : mColors{static_cast<T>(0)}
{
    size_t limit = ComponentCount < l.size() ? ComponentCount : l.size();
    size_t ctr = 0;
    for (auto& item: l)
    {
        if (ctr == limit)
        {
            break;
        }

        mColors[ctr] = item;
        ctr++;
    }
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>& Pixel<T, ComponentCount>::operator=(std::initializer_list<T> l)
{
    memset(mColors, 0x0, sizeof(T) * ComponentCount);

    size_t limit = ComponentCount < l.size() ? ComponentCount : l.size();
    size_t ctr = 0;
    for (auto& item: l)
    {
        if (ctr == limit)
        {
            break;
        }

        mColors[ctr] = item;
        ctr++;
    }
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>::Pixel(const Pixel<T, ComponentCount>& other)
{
    for (size_t i = 0; i < ComponentCount; ++i)
        mColors[i] = other.mColors[i];
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>::Pixel(Pixel<T, ComponentCount>&& other)
{
    for (size_t i = 0; i < ComponentCount; ++i)
        mColors[i] = other.mColors[i];

    memset(other.mColors, 0x0, sizeof(T) * ComponentCount);
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>& Pixel<T, ComponentCount>::operator=(const Pixel<T, ComponentCount>& other)
{
    for (size_t i = 0; i < ComponentCount; ++i)
        mColors[i] = other.mColors[i];
    return *this;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>& Pixel<T, ComponentCount>::operator=(Pixel<T, ComponentCount>&& other)
{
    for (size_t i = 0; i < ComponentCount; ++i)
        mColors[i] = other.mColors[i];

    memset(other.mColors, 0x0, sizeof(T) * ComponentCount);
    return *this;
}


template <typename T, size_t ComponentCount>
bool Pixel<T, ComponentCount>::operator==(const Pixel<T, ComponentCount>& other) const
{
    for (size_t i = 0; i < ComponentCount; ++i)
    {
        if (mColors[i] != other.mColors[i])
            return false;
    }

    return true;
}

template <typename T, size_t ComponentCount>
bool Pixel<T, ComponentCount>::operator!=(const Pixel<T, ComponentCount>& other) const
{
    for (size_t i = 0; i < ComponentCount; ++i)
    {
        if (mColors[i] != other.mColors[i])
            return true;
    }

    return false;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>& Pixel<T, ComponentCount>::operator+=(const Pixel<T, ComponentCount>& other)
{
    for (uint32_t i = 0; i < ComponentCount; ++i)
        mColors[i] += other.mColors[i];
    return *this;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>& Pixel<T, ComponentCount>::operator-=(const Pixel<T, ComponentCount>& other)
{
    for (uint32_t i = 0; i < ComponentCount; ++i)
        mColors[i] -= other.mColors[i];
    return *this;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>& Pixel<T, ComponentCount>::operator*=(const Pixel<T, ComponentCount>& other)
{
    for (uint32_t i = 0; i < ComponentCount; ++i)
        mColors[i] *= other.mColors[i];
    return *this;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>& Pixel<T, ComponentCount>::operator/=(const Pixel<T, ComponentCount>& other)
{
    for (uint32_t i = 0; i < ComponentCount; ++i)
        mColors[i] /= other.mColors[i];
    return *this;
}


template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>& Pixel<T, ComponentCount>::operator+=(const T& other)
{
    for (uint32_t i = 0; i < ComponentCount; ++i)
        mColors[i] += other;
    return *this;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>& Pixel<T, ComponentCount>::operator-=(const T& other)
{
    for (uint32_t i = 0; i < ComponentCount; ++i)
        mColors[i] -= other;
    return *this;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>& Pixel<T, ComponentCount>::operator*=(const T& other)
{
    for (uint32_t i = 0; i < ComponentCount; ++i)
        mColors[i] *= other;
    return *this;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount>& Pixel<T, ComponentCount>::operator/=(const T& other)
{
    for (uint32_t i = 0; i < ComponentCount; ++i)
        mColors[i] /= other;
    return *this;
}

template <typename T, size_t ComponentCount>
T Pixel<T, ComponentCount>::operator[](size_t i) const
{
    LKCOMMON_ASSERT(i < ComponentCount, "Too big index provided");
    return mColors[i];
}

template <typename T, size_t ComponentCount>
template <typename ConvType>
Pixel<T, ComponentCount>::operator Pixel<ConvType, ComponentCount>() const
{
    Pixel<ConvType, ComponentCount> p;

    for (size_t i = 0; i < ComponentCount; ++i)
    {
        p.mColors[i] = ConvertColor<T, ConvType>(mColors[i]);
    }

    return p;
}

template <size_t ComponentCount>
std::ostream& operator<< (std::ostream& o, const Pixel<uint8_t, ComponentCount>& p)
{
    o << "[";
    for (size_t i = 0; i < ComponentCount; ++i)
    {
        if (i != 0)
            o << ", ";
        o << static_cast<uint32_t>(p.mColors[i]);
    }
    o << "]";
    return o;
}

template <size_t ComponentCount>
std::ostream& operator<< (std::ostream& o, const Pixel<float, ComponentCount>& p)
{
    o << "[";
    for (size_t i = 0; i < ComponentCount; ++i)
    {
        if (i != 0)
            o << ", ";
        o << p.mColors[i];
    }
    o << "]";
    return o;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount> operator+ (Pixel<T, ComponentCount> lhs, const Pixel<T, ComponentCount>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount> operator- (Pixel<T, ComponentCount> lhs, const Pixel<T, ComponentCount>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount> operator* (Pixel<T, ComponentCount> lhs, const Pixel<T, ComponentCount>& rhs)
{
    lhs *= rhs;
    return lhs;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount> operator/ (Pixel<T, ComponentCount> lhs, const Pixel<T, ComponentCount>& rhs)
{
    lhs /= rhs;
    return lhs;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount> operator+ (Pixel<T, ComponentCount> lhs, const T& rhs)
{
    lhs += rhs;
    return lhs;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount> operator- (Pixel<T, ComponentCount> lhs, const T& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount> operator* (Pixel<T, ComponentCount> lhs, const T& rhs)
{
    lhs *= rhs;
    return lhs;
}

template <typename T, size_t ComponentCount>
Pixel<T, ComponentCount> operator/ (Pixel<T, ComponentCount> lhs, const T& rhs)
{
    lhs /= rhs;
    return lhs;
}


} // namespace Utils
} // namespace lkCommon