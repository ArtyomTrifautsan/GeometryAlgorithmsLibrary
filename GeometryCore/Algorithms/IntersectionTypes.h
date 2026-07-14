#pragma once

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
}