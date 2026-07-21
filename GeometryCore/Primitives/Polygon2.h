#pragma once

#include <vector>
#include <memory>

#include <GeometryCore/Primitives/Segment2.h>
#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/Primitives/Vector2.h>


namespace Geometry
{
	template <typename T>
	struct Polygon2
	{
		std::vector<Segment2<T>> edges{};

		Polygon2() = default;
		Polygon2(std::vector<Segment2<T>> edges_) : edges{std::move(edges_)} {}
	};
}