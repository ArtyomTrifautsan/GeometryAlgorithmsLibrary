#pragma once

#include <algorithm>

#include <GeometryCore/Primitives/Segment3.h>
#include <GeometryCore/Primitives/Point3.h>
#include <GeometryCore/Primitives/Vector3.h>
#include <GeometryCore/Math/Utils.h>
#include <GeometryCore/Math/Constants.h>
#include <GeometryCore/Algorithms/IntersectionTypes.h>
#include <GeometryCore/Algorithms/PointPointDistance3.h>


namespace Geometry
{
    template <typename T>
    struct PointSegmentDistance3
    {
        IntersectionType type = IntersectionType::None;
        T distance = 0;
    };

    template <typename T>
    [[nodiscard]] PointSegmentDistance3<T> Distance(const Segment3<T>& segment, const Point3<T>& point) noexcept
    {
        if (segment.IsDegenerate())
        {
            PointPointDistance3<T> auxResult = Distance(segment.start, point);
            return PointSegmentDistance3<T>{ auxResult.type, auxResult.distance };
        }

        Vector3<T> V = segment.Vector();
        Vector3<T> PS = point - segment.start;
        if (PS.Zero())
        {
            return PointSegmentDistance3<T>{ IntersectionType::Point, T(0)};
        }

        T t = Dot(V, PS) / V.SqrLen();
        t = std::clamp(t, T(0), T(1));
        Vector3<T> res = segment.PointAt(t) - point;

        if (res.Zero())
        {
            return PointSegmentDistance3<T>{ IntersectionType::Point, T(0) };
        }
        return PointSegmentDistance3<T>{ IntersectionType::None, res.Len() };
    }
}