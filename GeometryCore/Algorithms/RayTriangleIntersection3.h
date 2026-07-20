#pragma once

#include <GeometryCore/Primitives/Ray3.h>
#include <GeometryCore/Primitives/Triangle3.h>
#include <GeometryCore/Primitives/Segment3.h>
#include <GeometryCore/Primitives/Vector3.h>
#include <GeometryCore/Algorithms/IntersectionTypes.h>
#include <GeometryCore/Math/Utils.h>


namespace Geometry
{
    template <typename T>
    struct RayTriangleIntersection3
    {
        IntersectionType type = IntersectionType::None;

        T t{};
        T u{};
        T v{};

        Point3<T> point{};

        explicit operator bool() const { return type != IntersectionType::None; }
    };

    template <typename T>
    [[nodiscard]] RayTriangleIntersection3<T> Intersect(const Ray3<T>& ray, const Triangle3<T>& triangle) noexcept
    {
        RayTriangleIntersection3<T> result;

        Vector3<T> edge1 = triangle.V1 - triangle.V0;
        Vector3<T> edge2 = triangle.V2 - triangle.V0;
        Vector3<T> normal = Cross(edge1, edge2);

        if (triangle.IsDegenerate() || ray.direction.Zero())
        {
            return RayTriangleIntersection3<T>{IntersectionType::None};
        }

        Vector3<T> pvec = Cross(ray.direction, edge2);
        T det = Dot(edge1, pvec);

        Vector3<T> tvec = ray.origin - triangle.V0;

        T max_edge1 = std::max({ Abs(edge1.x), Abs(edge1.y), Abs(edge1.z) });
        T max_edge2 = std::max({ Abs(edge2.x), Abs(edge2.y), Abs(edge2.z) });
        T max_ray_direction = std::max({ Abs(ray.direction.x), Abs(ray.direction.y), Abs(ray.direction.z) });
        T max_scale = std::max({ max_edge1, max_edge2, max_ray_direction });

        T geometric_tolerance = EPSILON<T> * EPSILON<T> * EPSILON<T> * max_edge1 * max_ray_direction * max_edge2;

        T roundoff_tolerance = CrossRoundoffTolerance(ray.direction, edge2) + 
            DotRoundoffTolerance(edge1, pvec) + 
            std::numeric_limits<T>::epsilon() * Abs(det);

        T D_tolerance = std::max(geometric_tolerance, roundoff_tolerance);
        if (IsZero(det, D_tolerance))
        {
            return RayTriangleIntersection3<T>{IntersectionType::None};
        }

        T inv_det = T(1) / det;

        T u = Dot(tvec, pvec) * inv_det;
        if (!( IsGreaterOrEqual(u, T(0)) && IsLessOrEqual(u, T(1)) ))
        {
            return RayTriangleIntersection3<T>{IntersectionType::None};
        }

        Vector3<T> qvec = Cross(tvec, edge1);
        T v = Dot(ray.direction, qvec) * inv_det;
        if (!( IsGreaterOrEqual(v, T(0)) && IsLessOrEqual(u + v, T(1)) ))
        {
            return RayTriangleIntersection3<T>{IntersectionType::None};
        }

        T t = Dot(edge2, qvec) * inv_det;
        if (!IsGreaterOrEqual(t, T(0)))
        {
            return RayTriangleIntersection3<T>{IntersectionType::None};
        }

        result.type = IntersectionType::Point;
        result.t = t;
        result.u = u;
        result.v = v;
        result.point = Point3<T>{triangle.V0 + edge1 * u + edge2 * v};

        return result;
    }
}