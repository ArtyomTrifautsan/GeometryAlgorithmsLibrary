#pragma once

#include <GeometryCore/Primitives/Segment3.h>
#include <GeometryCore/Primitives/Point3.h>
#include <GeometryCore/Primitives/Vector3.h>
#include <GeometryCore/Math/Utils.h>
#include <GeometryCore/Math/Constants.h>
#include <GeometryCore/Algorithms/IntersectionTypes.h>
#include <GeometryCore/Algorithms/PointSegmentDistance3.h>
#include <GeometryCore/Algorithms/PointPointDistance3.h>


namespace Geometry
{
    template <typename T>
    struct SegmentSegmentDistance3
    {
        IntersectionType type = IntersectionType::None;

        T distance = 0;
        Point3<T> point1{};
        Point3<T> point2{};
        Segment3<T> segment{};

        explicit operator bool() const
        {
            return type != IntersectionType::None;
        }
    };

	template <typename T>
    SegmentSegmentDistance3<T> Distance(const Segment3<T>& first, const Segment3<T>& second)
	{
        bool IsDegFirst = first.IsDegenerate();
        bool IsDegSecond = second.IsDegenerate();

        if (IsDegFirst && IsDegSecond)
        {
            PointPointDistance3 aux_res = Distance(first.start, second.start);
            return SegmentSegmentDistance3<T>{
                aux_res.type,
                aux_res.distance,
                first.start,
                second.start,
                {}
            };
        }
        else if (IsDegFirst)
        {
            PointSegmentDistance3 aux_res = Distance(second, first.start);
            return SegmentSegmentDistance3<T>{
                aux_res.type,
                aux_res.distance,
                first.start,
                aux_res.point,
                {}
            };
        }
        else if (IsDegSecond)
        {
            PointSegmentDistance3 aux_res = Distance(first, second.start);
            return SegmentSegmentDistance3<T>{
                aux_res.type,
                aux_res.distance,
                aux_res.point,
                second.start,
                {}
            };
        }

        Vector3<T> u = first.Vector();
        Vector3<T> v = second.Vector();
        Vector3<T> W0 = first.start - second.start;

        T a = Dot(u, u);
        T b = Dot(u, v);
        T c = Dot(v, v);
        T d = Dot(u, W0);
        T e = Dot(v, W0);

        T D = a * c - b * b;

        T max_u = std::max({ Abs(u.x), Abs(u.y), Abs(u.z) });
        T max_v = std::max({ Abs(v.x), Abs(v.y), Abs(v.z) });
        T max_scale = std::max(max_u, max_v);

        T geometric_tolerance = EPSILON<T> * EPSILON<T> * max_scale * max_scale;
        T roundoff_tolerance = EPSILON<T> * (Abs(a * c) + Abs(b * b));
        T D_tolerance = std::max(geometric_tolerance, roundoff_tolerance);

        T sn, sd;
        T tn, td;

        bool areCollinear = (D < D_tolerance);

        if (areCollinear)
        {
            sn = T(0);
            sd = T(1);
            tn = e;
            td = c;
        }
        else
        {
            sn = (b * e - c * d);
            sd = D;
            tn = (a * e - b * d);
            td = D;
        }

        // Clipping sc into [0, 1]
        if (sn < T(0))
        {
            sn = T(0);
            tn = e;
            td = c;
        }
        else if (sn > sd)
        {
            sn = sd;
            tn = e + b;
            td = c;
        }

        // Clipping tc into [0, 1]
        if (tn < T(0))
        {
            tn = T(0);

            if (-d < T(0))
            {
                sn = T(0);
            }
            else if (-d > a)
            {
                sn = sd;
            }
            else
            {
                sn = -d;
                sd = a;
            }
        }
        else if (tn > td)
        {
            tn = td;
            
            if ((-d + b) < T(0))
            {
                sn = T(0);
            }
            else if ((-d + b) > a)
            {
                sn = sd;
            }
            else
            {
                sn = -d + b;
                sd = a;
            }
        }

        T s = IsZero(sd) ? T(0) : sn / sd;
        T t = IsZero(td) ? T(0) : tn / td;

        Point3<T> P1 = first.PointAt(s);
        Point3<T> P2 = second.PointAt(t);
        T distance = (P1 - P2).Len();

        IntersectionType final_type = IntersectionType::None;
        Segment3<T> overlap_segment{};

        T intersection_tolerance = EPSILON<T> *max_scale;
        if (IsZero(distance, intersection_tolerance))
        {
            if (areCollinear)
            {
                T s0 = -d / a;
                T s1 = (-d + b) / a;

                T s_min = std::min(s0, s1);
                T s_max = std::max(s0, s1);

                s_min = std::max(T(0), s_min);
                s_max = std::min(T(1), s_max);

                if (s_min <= s_max)
                {
                    if (AreEqual(s_min, s_max))
                    {
                        final_type = IntersectionType::Point;
                        P1 = first.PointAt(s_min);
                        P2 = P1;
                    }
                    else
                    {
                        final_type = IntersectionType::Segment;
                        overlap_segment = Segment3<T>(first.PointAt(s_min), first.PointAt(s_max));
                    }
                }
                else
                {
                    final_type = IntersectionType::None;
                }
            }
            else
            {
                final_type = IntersectionType::Point;
            }
        }
        else
        {
            final_type = IntersectionType::None;
        }

        return SegmentSegmentDistance3<T>{
            final_type,
            distance,
            P1,
            P2,
            overlap_segment
        };
	}
}