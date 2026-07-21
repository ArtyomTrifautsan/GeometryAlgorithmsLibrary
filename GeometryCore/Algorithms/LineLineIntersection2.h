#pragma once

#include <GeometryCore/Primitives/Line2.h>
#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/Primitives/Vector2.h>
#include <GeometryCore/Math/Utils.h>
#include <GeometryCore/Algorithms/IntersectionTypes.h>


namespace Geometry
{
    template <typename T>
    struct LineLineIntersection2
    {
        IntersectionType type = IntersectionType::None;

        Point2<T> point{};
        T ta{};
        T tb{};

        explicit operator bool() const { return type != IntersectionType::None; }
    };

    template <typename T>
    [[nodiscard]] LineLineIntersection2<T> Intersect(const Line2<T>& first, const Line2<T>& second) noexcept
    {
        bool IsDegenerateA = first.direction.Zero();
        bool IsDegenerateB = second.direction.Zero();

        if (IsDegenerateA && IsDegenerateB)
        {
            if (AreEqual(first.origin, second.origin))
            {
                return LineLineIntersection2<T>{ IntersectionType::Point, first.origin };
            }
            return { IntersectionType::None };
        }
        else if (IsDegenerateA)
        {
            if (second.ContainsPoint(first.origin))
            {
                return LineLineIntersection2<T>{ IntersectionType::Point, first.origin };
            }
            return { IntersectionType::None };
        }
        else if (IsDegenerateB)
        {
            if (first.ContainsPoint(second.origin))
            {
                return LineLineIntersection2<T>{ IntersectionType::Point, second.origin };
            }
            return { IntersectionType::None };
        }

        Vector2<T> vDelta = second.origin - first.origin;

        T D = Cross(first.direction, second.direction);
        T D_tolerance = EPSILON<T> * (Abs(first.direction.x * second.direction.y) + Abs(first.direction.y * second.direction.x));

        if (!IsZero(D, D_tolerance))
        {
            T invD = T(1.0 / D);
            T ta = Cross(vDelta, second.direction) * invD;
            T tb = Cross(vDelta, first.direction) * invD;
            return { IntersectionType::Point, first.origin + first.direction * ta, ta, tb };
        }

        T delta = Cross(vDelta, first.direction);
        T delta_tolerance = EPSILON<T> * (Abs(vDelta.x * first.direction.y) + Abs(vDelta.y * first.direction.x));

        if (!IsZero(delta, delta_tolerance))
        {
            return { IntersectionType::None, {}, T(0), T(0) };
        }

        return { IntersectionType::Line, {}, T(0), T(0) };
    }
}