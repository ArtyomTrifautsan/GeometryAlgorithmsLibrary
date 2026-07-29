#pragma once

#include <GeometryCore/Primitives/Segment2.h>
#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/Primitives/Vector2.h>
#include <GeometryCore/Math/Utils.h>
#include <GeometryCore/Math/Constants.h>
#include <GeometryCore/Algorithms/IntersectionTypes.h>

namespace Geometry
{
    template <typename T>
    struct PointPointDistance2
    {
        IntersectionType type = IntersectionType::None;
        T distance = 0;
    };

    template <typename T>
    [[nodiscard]] PointPointDistance2<T> Distance(const Point2<T>& first, const Point2<T>& second) noexcept
    {
        T dist = (second - first).Len();

        if (IsZero(dist))
        {
            return PointPointDistance2<T>{ IntersectionType::Point, T(0) };
        }

        return PointPointDistance2<T>{ IntersectionType::None, dist };
    }
}