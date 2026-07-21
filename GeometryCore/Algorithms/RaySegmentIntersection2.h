#pragma once

#include <algorithm>

#include <GeometryCore/Algorithms/LineLineIntersection2.h>
#include <GeometryCore/Primitives/Ray2.h>
#include <GeometryCore/Primitives/Segment2.h>
#include <GeometryCore/Algorithms/IntersectionTypes.h>


namespace Geometry
{
    template <typename T>
    struct RaySegmentIntersection2
    {
        IntersectionType type = IntersectionType::None;

        Point2<T> point{};
        Segment2<T> segment{};

        explicit operator bool() const { return type != IntersectionType::None; }
    };

    template <typename T>
    [[nodiscard]] RaySegmentIntersection2<T> Intersect(const Ray2<T>& ray, const Segment2<T>& seg) noexcept
    {
        bool isDegenerateRay = ray.direction.Zero();
        bool isDegenerateSeg = seg.IsDegenerate();

        if (isDegenerateRay && isDegenerateSeg)
        {
            if (AreEqual(ray.origin, seg.start))
            {
                return RaySegmentIntersection2<T>{ IntersectionType::Point, ray.origin };
            }
            return { IntersectionType::None };
        }
        else if (isDegenerateRay)
        {
            if (seg.ContainsPoint(ray.origin))
            {
                return RaySegmentIntersection2<T>{ IntersectionType::Point, ray.origin };
            }
            return { IntersectionType::None };
        }
        else if (isDegenerateSeg)
        {
            if (ray.ContainsPoint(seg.start))
            {
                return RaySegmentIntersection2<T>{ IntersectionType::Point, seg.start };
            }
            return { IntersectionType::None };
        }

        const Vector2<T>& dirRay = ray.direction;
        const Vector2<T>& dirSeg = seg.Vector();

        auto LineIntersectionInfo = Intersect(Line2<T>{ray.origin, dirRay}, Line2<T>{seg.start, dirSeg});

        if (LineIntersectionInfo.type == IntersectionType::Point)
        {
            if (IsGreaterOrEqual(LineIntersectionInfo.ta, T(0)) &&
                IsGreaterOrEqual(LineIntersectionInfo.tb, T(0)) && IsLessOrEqual(LineIntersectionInfo.tb, T(1)))
            {
                return { IntersectionType::Point, LineIntersectionInfo.point };
            }
            return { IntersectionType::None };
        }

        if (LineIntersectionInfo.type == IntersectionType::Line)
        {
            T d1 = Dot(seg.start - ray.origin, dirRay);
            T d2 = Dot(seg.end - ray.origin, dirRay);

            T d_min = std::min(d1, d2);
            T d_max = std::max(d1, d2);

            if (!IsGreaterOrEqual(d_max, T(0)))
            {
                return { IntersectionType::None };
            }

            if (IsZero(d_max))
            {
                return { IntersectionType::Point, ray.origin };
            }

            if (!IsGreaterOrEqual(d_min, T(0)))
            {
                Point2<T> endPt = (d1 > d2) ? seg.start : seg.end;
                return { IntersectionType::Segment, {}, Segment2<T>(ray.origin, endPt) };
            }

            return { IntersectionType::Segment, {}, seg };
        }

        return { IntersectionType::None };
    }
}