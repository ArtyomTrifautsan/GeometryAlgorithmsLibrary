#pragma once

#include <cmath>

#include "Point3.h"
#include "Vector3.h"

namespace Geometry
{
    template <typename T>
    struct Segment3
    {
        Point3<T> start = {};
        Point3<T> end = {};

        Segment3() = default;
        Segment3(Point3<T> start_, Point3<T> end_) noexcept : start{ start_ }, end{ end_ } {}

        [[nodiscard]] constexpr Vector3<T> Vector() const noexcept { return end - start; }

        [[nodiscard]] constexpr T SqrLength() const noexcept
        {
            return (start.x - end.x) * (start.x - end.x) +
                (start.y - end.y) * (start.y - end.y) +
                (start.z - end.z) * (start.z - end.z);
        }

        [[nodiscard]] T Length() const noexcept { return std::sqrt(SqrLength()); }

        [[nodiscard]] constexpr Point3<T> Midpoint() const noexcept
        {
            return Point3<T>{(start.x + end.x) / T(2), (start.y + end.y) / T(2), (start.z + end.z) / T(2)};
        }

        [[nodiscard]] constexpr Point3<T> PointAt(T t) const noexcept
        {
            return start + Vector() * t;
        }
    };
}