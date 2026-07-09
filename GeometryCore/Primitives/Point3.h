#pragma once

#include <GeometryCore/Primitives/Vector3.h>
#include <GeometryCore/Math/Utils.h>


namespace Geometry
{
    template <typename T>
    struct Point3
    {
        T x = 0;
        T y = 0;
        T z = 0;

        constexpr Point3() = default;
        constexpr Point3(T x_, T y_, T z_) : x{ x_ }, y{ y_ }, z{ z_ } {}

        constexpr Point3& operator+=(const Vector3<T>& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        constexpr Point3& operator-=(const Vector3<T>& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
    };

    template <typename T>
    [[nodiscard]] constexpr Vector3<T> operator-(const Point3<T>& lhs, const Point3<T>& rhs)
    {
        return Vector3<T>{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
    }

    template <typename T>
    [[nodiscard]] constexpr Point3<T> operator+(Point3<T> p, const Vector3<T>& v)
    {
        p += v;
        return p;
    }

    template <typename T>
    [[nodiscard]] constexpr Point3<T> operator-(Point3<T> p, const Vector3<T>& v)
    {
        p -= v;
        return p;
    }

    template <typename T>
    [[nodiscard]] constexpr bool AreEqual(const Point3<T>& lhs, const Point3<T>& rhs) noexcept
    {
        return AreEqual(lhs.x, rhs.x) && AreEqual(lhs.y, rhs.y) && AreEqual(lhs.z, rhs.z);
    }
}