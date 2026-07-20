#pragma once

#include <GeometryCore/Primitives/Plane3.h>
#include <GeometryCore/Primitives/Segment3.h>
#include <GeometryCore/Algorithms/IntersectionTypes.h>
#include <GeometryCore/Math/Utils.h>


namespace Geometry
{
    template <typename T>
    struct SegmentPlaneIntersection3
    {
        IntersectionType type = IntersectionType::None;

        Point3<T> point{};
        Segment3<T> overlap_segment{};

        explicit operator bool() const { return type != IntersectionType::None; }
    };

    template <typename T>
    [[nodiscard]] SegmentPlaneIntersection3<T> Intersect(const Segment3<T>& segment, const Plane3<T>& plane) noexcept
    {
		Vector3<T> v = segment.Vector();
		Vector3<T> u = segment.start - plane.origin;

        T numerator = -Dot(u, plane.normal);
        T denominator = Dot(v, plane.normal);

        if (segment.IsDegenerate())
        {
            if (IsZero(numerator))
            {
                return SegmentPlaneIntersection3<T>{IntersectionType::Point, segment.start, {}};
            }

            return SegmentPlaneIntersection3<T>{IntersectionType::None, {}, {}};
        }

        if (IsZero(denominator))
        {
            if (IsZero(numerator))
            {
                return SegmentPlaneIntersection3<T>{IntersectionType::Segment, segment.start, segment};
            }
            return SegmentPlaneIntersection3<T>{IntersectionType::None, {}, {}};
        }

		T t = numerator / denominator;

        if (IsGreaterOrEqual(t, T(0)) && IsLessOrEqual(t, T(1)))
        {
            t = std::clamp(t, T(0), T(1));
            return SegmentPlaneIntersection3<T>{IntersectionType::Point, segment.PointAt(t), {}};
        }

        return SegmentPlaneIntersection3<T>{IntersectionType::None, {}, {}};
    }
}