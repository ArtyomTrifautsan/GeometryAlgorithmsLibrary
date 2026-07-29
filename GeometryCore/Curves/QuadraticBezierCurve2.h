#pragma once

#include <utility>
#include <GeometryCore/Primitives/Point2.h>


namespace Geometry
{
	template <typename T>
	struct QuadraticBezierCurve2
	{
		Point2<T> p0;
		Point2<T> p1;
		Point2<T> p2;

		constexpr QuadraticBezierCurve2() = default;
		constexpr QuadraticBezierCurve2(Point2<T> P0, Point2<T> P1, Point2<T> P2) noexcept 
			: p0{ P0 }, p1{ P1 }, p2{ P2 } {}

		constexpr Point2<T>& operator[](size_t index) noexcept
		{
			if (index == 0) return p0;
			if (index == 1) return p1;
			return p2;
		}
		constexpr const Point2<T>& operator[](size_t index) const noexcept
		{
			if (index == 0) return p0;
			if (index == 1) return p1;
			return p2;
		}

		constexpr Point2<T> PointAt(T t) const noexcept
		{
			const Point2<T> q0 = p0 + t * (p1 - p0);
			const Point2<T> q1 = p1 + t * (p2 - p1);

			return q0 + t * (q1 - q0);
		}

		constexpr Vector2<T> DerivativeAt(T t) const noexcept
		{
			const Vector2<T> v0 = p1 - p0;
			const Vector2<T> v1 = p2 - p1;
			return T(2) * (T(1) - t) * v0 + T(2) * t * v1;
		}

		constexpr std::pair<QuadraticBezierCurve2, QuadraticBezierCurve2> Subdivide(T t) const noexcept
		{
			const Point2<T> q0 = p0 + t * (p1 - p0);
			const Point2<T> q1 = p1 + t * (p2 - p1);
			const Point2<T> r0 = q0 + t * (q1 - q0);

			return {
				QuadraticBezierCurve2{ p0, q0, r0 },
				QuadraticBezierCurve2{ r0, q1, p2 }
			};
		}
	};
}