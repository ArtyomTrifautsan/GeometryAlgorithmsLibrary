#pragma once

#include <GeometryCore/Primitives/Polygon2.h>
#include <GeometryCore/Primitives/Segment2.h>
#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/Primitives/Vector2.h>
#include <GeometryCore/Math/Utils.h>
#include <GeometryCore/Math/Constants.h>
#include <GeometryCore/Algorithms/IntersectionTypes.h>
#include <GeometryCore/Algorithms/LocationTypes.h>


namespace Geometry
{
	template <typename T>
	LocationType PointPolygonLocation(const Polygon2<T>& polygon, const Point2<T>& point)
	{
		size_t intersections = 0;

		for (const auto& edge : polygon.edges)
		{

		}
	}
}