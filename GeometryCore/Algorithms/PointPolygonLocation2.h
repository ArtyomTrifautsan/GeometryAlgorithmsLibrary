#pragma once

#include <GeometryCore/Algorithms/RaySegmentIntersection2.h>
#include <GeometryCore/Algorithms/IntersectionTypes.h>
#include <GeometryCore/Algorithms/LocationTypes.h>
#include <GeometryCore/Primitives/Polygon2.h>
#include <GeometryCore/Primitives/Segment2.h>
#include <GeometryCore/Primitives/Ray2.h>
#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/Primitives/Vector2.h>
#include <GeometryCore/Math/Utils.h>
#include <GeometryCore/Math/Constants.h>


namespace Geometry
{
	template <typename T>
	LocationType PointPolygonLocation(const Polygon2<T>& polygon, const Point2<T>& point)
	{
		if (!polygon.Valid())
		{
			return LocationType::Invalid;
		}

        if (!polygon.bounds.Contains(point))
        {
            return LocationType::Outside;
        }

        bool inside = false;
        size_t len = polygon.vertices.size();

        for (size_t i = 0; i < len; ++i)
        {
            Segment2<T> edge = polygon.GetEdge(i);

            if (edge.ContainsPoint(point))
            {
                return LocationType::OnBoundary;
            }

            bool startAbove = IsGreaterOrEqual(edge.start.y, point.y);
            bool endAbove = IsGreaterOrEqual(edge.end.y, point.y);


            if (startAbove != endAbove)
            {
                T intersectX = edge.start.x + (point.y - edge.start.y) * (edge.end.x - edge.start.x) / (edge.end.y - edge.start.y);

                if (intersectX > point.x)
                {
                    inside = !inside;
                }
            }
        }

        return inside ? LocationType::Inside : LocationType::Outside;
    }
}