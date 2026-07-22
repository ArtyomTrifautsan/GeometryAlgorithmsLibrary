#pragma once

#include <algorithm>
#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/Math/Utils.h>
#include <GeometryCore/Math/Constants.h>

namespace Geometry
{
    template <typename T>
    struct AABB2
    {
        Point2<T> min{};
        Point2<T> max{};

        constexpr AABB2() = default;
        constexpr AABB2(const Point2<T>& min_, const Point2<T>& max_) noexcept
            : min{ min_ }, max{ max_ }
        {}

        [[nodiscard]] constexpr bool Contains(const Point2<T>& point) const noexcept
        {
            return IsGreaterOrEqual(point.x, min.x) && IsLessOrEqual(point.x, max.x) &&
                IsGreaterOrEqual(point.y, min.y) && IsLessOrEqual(point.y, max.y);
        }
    };
}