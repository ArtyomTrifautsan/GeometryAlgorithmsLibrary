#pragma once

#include <GeometryCore/Primitives/Segment3.h>
#include <GeometryCore/Primitives/Point3.h>
#include <GeometryCore/Primitives/Vector3.h>
#include <GeometryCore/Math/Utils.h>
#include <GeometryCore/Math/Constants.h>
#include <GeometryCore/Algorithms/IntersectionTypes.h>

namespace Geometry
{
    template <typename T>
    struct PointPointDistance3
    {
        IntersectionType type = IntersectionType::None;
        T distance = 0;
    };

    template <typename T>
    [[nodiscard]] PointPointDistance3<T> Distance(const Point3<T>& first, const Point3<T>& second) noexcept
    {
        T dist = (second - first).Len();

        if (IsZero(dist))
        {
            return PointPointDistance3<T>{ IntersectionType::Point, T(0) };
        }

        return PointPointDistance3<T>{ IntersectionType::None, dist };
    }
}