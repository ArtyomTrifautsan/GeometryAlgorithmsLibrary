#pragma once

#include <cmath>

#include "Point2.h"
#include "Vector2.h"


namespace Geometry
{
	template <typename T>
	struct Segment2
	{
		Point2<T> start = {};
		Point2<T> end = {};

		Segment2() = default;
		Segment2(Point2<T> start_, Point2<T> end_) noexcept : start{start_}, end{end_} {}

		[[nodiscard]] constexpr Vector2<T> Vector() const noexcept { return end - start; }

		[[nodiscard]] constexpr T SqrLength() const noexcept
		{
			return (start.x - end.x) * (start.x - end.x) + (start.y - end.y) * (start.y - end.y);
		}

		[[nodiscard]] T Length() const noexcept { return std::sqrt(SqrLength()); }

		[[nodiscard]] constexpr Point2<T> Midpoint() const noexcept
		{
			return start + Vector() * T(0.5);
		}
	};
}