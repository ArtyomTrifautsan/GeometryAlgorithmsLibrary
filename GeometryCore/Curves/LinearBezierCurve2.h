#pragma once

#include <utility>
#include <GeometryCore/Primitives/Point2.h>
//#include <GeometryCore/Math/Utils.h>


namespace Geometry
{
	template <typename T>
	struct LinearBezierCurve2
	{
		Point2<T> p0;
		Point2<T> p1;

		constexpr LinearBezierCurve2() = default;
		constexpr LinearBezierCurve2(Point2<T> P0, Point2<T> P1) noexcept : p0{ P0 }, p1{ P1 } {}

		constexpr Point2<T>& operator[](size_t index) noexcept
		{
			return (index == 0) ? p0 : p1;
		}
		constexpr const Point2<T>& operator[](size_t index) const noexcept
		{
			return (index == 0) ? p0 : p1;
		}

		constexpr Point2<T> PointAt(T t) const noexcept
		{
			//if (IsGreaterOrEqual(t, 0) && IsLessOrEqual(t, 1))
			return p0 + t * (p1 - p0);
		}

		constexpr Vector2<T> Derivative() const noexcept
		{
			return p1 - p0;
		}

		constexpr std::pair<LinearBezierCurve2, LinearBezierCurve2> Subdivide(T t) const noexcept
		{
			const Point2<T> m = PointAt(t);
			return { LinearBezierCurve2{ p0, m }, LinearBezierCurve2{ m, p1 } };
		}
	};
}