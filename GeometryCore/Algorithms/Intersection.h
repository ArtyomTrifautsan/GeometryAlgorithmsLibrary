#pragma once

#include <GeometryCore/Primitives/Segment2.h>
#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/Primitives/Vector2.h>
#include <GeometryCore/Math/Utils.h>
#include <GeometryCore/Math/Constants.h>


namespace Geometry
{

	enum class IntersectionType
	{
		None,
		Point,
		Points,     // Two points of intersection (for example: ray-sphere, ray-circle)
		Segment,
		Line,
		Polygon
	};


	template <typename T>
	struct SegmentSegmentIntersection2
	{
		IntersectionType type = IntersectionType::None;

		// Results, special for this case in 2D
		Point2<T> point{};
		Segment2<T> segment{};

		explicit operator bool() const { return type != IntersectionType::None; }
	};


	template <typename T>
	SegmentSegmentIntersection2<T> Intersect(const Segment2<T>& a, const Segment2<T>& b)
	{
		bool IsDegenerateA = a.IsDegenerate();
		bool IsDegenerateB = b.IsDegenerate();

		if (IsDegenerateA && IsDegenerateB)
		{
			if (AreEqual(a.start, b.start))
			{
				return SegmentSegmentIntersection2<T>{ IntersectionType::Point, a.start };
			}
			return { IntersectionType::None };
		}
		else if (IsDegenerateA)
		{
			if (b.ContainsPoint(a.start))
			{
				return SegmentSegmentIntersection2<T>{ IntersectionType::Point, a.start };
			}
			return { IntersectionType::None };
		}
		else if (IsDegenerateB)
		{
			if (a.ContainsPoint(b.start))
			{
				return SegmentSegmentIntersection2<T>{ IntersectionType::Point, b.start };
			}
			return { IntersectionType::None };
		}

		Vector2<T> Va = a.Vector();
		Vector2<T> Vb = b.Vector();
		Vector2<T> Vdelta = b.start - a.start;

		T D = Cross(Va, Vb);
		T D_tolerance = EPSILON<T> * (Abs(Va.x * Vb.y) + Abs(Va.y * Vb.x));

		if (!IsZero(D, D_tolerance))
		{
			T invD = T(1.0 / D);
			T ta = Cross(Vdelta, Vb) * invD;
			T tb = Cross(Vdelta, Va) * invD;

			if (IsGreaterOrEqual(ta, T(0)) && IsLessOrEqual(ta, T(1)) &&
				IsGreaterOrEqual(tb, T(0)) && IsLessOrEqual(tb, T(1)))
			{
				Point2<T> intersectionPoint = a.PointAt(ta);
				return SegmentSegmentIntersection2<T>{ IntersectionType::Point, intersectionPoint };
			}
			else
			{
				return { IntersectionType::None };
			}
		}

		T delta = Cross(Vdelta, Va);
		T delta_tolerance = EPSILON<T> *(Abs(Vdelta.x * Va.y) + Abs(Vdelta.y * Va.x));

		if (!IsZero(delta, delta_tolerance))
		{
			return { IntersectionType::None };
		}

		bool overlapping = false;
		bool useX = Abs(Va.x) > Abs(Va.y);

		if (useX)
		{
			T min1 = std::min(a.start.x, a.end.x);
			T max1 = std::max(a.start.x, a.end.x);
			T min2 = std::min(b.start.x, b.end.x);
			T max2 = std::max(b.start.x, b.end.x);

			overlapping = IsGreaterOrEqual(max1, min2) && IsLessOrEqual(min1, max2);
		}
		else
		{
			T min1 = std::min(a.start.y, a.end.y);
			T max1 = std::max(a.start.y, a.end.y);
			T min2 = std::min(b.start.y, b.end.y);
			T max2 = std::max(b.start.y, b.end.y);

			overlapping = IsGreaterOrEqual(max1, min2) && IsLessOrEqual(min1, max2);
		}

		if (overlapping)
		{
			Point2<T> points[4] = { a.start, a.end, b.start, b.end };

			if (useX)
			{
				std::sort(std::begin(points), std::end(points), [](const Point2<T>& lhs, const Point2<T>& rhs) {
					return lhs.x < rhs.x;
				});
			}
			else
			{
				std::sort(std::begin(points), std::end(points), [](const Point2<T>& lhs, const Point2<T>& rhs) {
					return lhs.y < rhs.y;
				});
			}

			Point2<T> p1 = points[1];
			Point2<T> p2 = points[2];

			// The case when segments overlay at one point
			if (AreEqual(p1, p2))
			{
				return SegmentSegmentIntersection2<T>{ IntersectionType::Point, p1 };
			}

			return SegmentSegmentIntersection2<T>{ IntersectionType::Segment, {}, Segment2<T>(p1, p2) };
		}

		return { IntersectionType::None };
	}
}