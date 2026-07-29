#pragma once

#include <algorithm>

#include <GeometryCore/Primitives/Segment2.h>
#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/Primitives/Vector2.h>
#include <GeometryCore/Math/Utils.h>
#include <GeometryCore/Math/Constants.h>
#include <GeometryCore/Algorithms/IntersectionTypes.h>
#include <GeometryCore/Algorithms/PointPointDistance2.h>


namespace Geometry
{
	template <typename T>
	struct PointSegmentDistance2
	{
		IntersectionType type = IntersectionType::None;
		T distance = 0;
		Point2<T> closest_point{};  // closest point on segment
	};


	template <typename T>
	[[nodiscard]] PointSegmentDistance2<T> Distance(const Point2<T>& point, const Segment2<T>& segment) noexcept
	{
		if (segment.IsDegenerate())
		{
			PointPointDistance2<T> auxResult = Distance(segment.start, point);
			return PointSegmentDistance2<T>{ auxResult.type, auxResult.distance, segment.start };
		}

		Vector2<T> V = segment.Vector();
		Vector2<T> PS = point - segment.start;
		if (PS.Zero())
		{
			return PointSegmentDistance2<T>{ IntersectionType::Point, T(0), segment.start};
		}

		T t = Dot(V, PS) / V.SqrLen();
		t = std::clamp(t, T(0), T(1));
		Point2<T> closest = segment.PointAt(t);
		Vector2<T> res = closest - point;

		if (res.Zero())
		{
			return PointSegmentDistance2<T>{ IntersectionType::Point, T(0), closest };
		}
		return PointSegmentDistance2<T>{ IntersectionType::None, res.Len(), closest };
	}
}