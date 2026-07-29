#pragma once

#include <GeometryCore/Primitives/Point2.h>


namespace Geometry
{
	template <typename T>
	struct CubicBezierCurve2
	{
		Point2<T> p0;
		Point2<T> p1;
		Point2<T> p2;
		Point2<T> p3;

		constexpr CubicBezierCurve2() = default;
		constexpr CubicBezierCurve2(Point2<T> P0, Point2<T> P1, Point2<T> P2, Point2<T> P3) noexcept
			: p0{ P0 }, p1{ P1 }, p2{ P2 }, p3{ P3 } {
		}

		constexpr Point2<T>& operator[](size_t index) noexcept
		{
			if (index == 0) return p0;
			if (index == 1) return p1;
			if (index == 2) return p2;
			return p3;
		}
		constexpr const Point2<T>& operator[](size_t index) const noexcept
		{
			if (index == 0) return p0;
			if (index == 1) return p1;
			if (index == 2) return p2;
			return p3;
		}

		constexpr Point2<T> PointAt(T t) const noexcept
		{
			const Point2<T> q0 = p0 + t * (p1 - p0);
			const Point2<T> q1 = p1 + t * (p2 - p1);
			const Point2<T> q2 = p2 + t * (p3 - p2);

			const Point2<T> r0 = q0 + t * (q1 - q0);
			const Point2<T> r1 = q1 + t * (q2 - q1);

			return r0 + t * (r1 - r0);
		}

		constexpr Vector2<T> DerivativeAt(T t) const noexcept
		{
			const T u = T(1) - t;
			const Vector2<T> v0 = p1 - p0;
			const Vector2<T> v1 = p2 - p1;
			const Vector2<T> v2 = p3 - p2;

			return T(3) * u * u * v0 + T(6) * u * t * v1 + T(3) * t * t * v2;
		}

		constexpr std::pair<CubicBezierCurve2, CubicBezierCurve2> Subdivide(T t) const noexcept
		{
			const Point2<T> q0 = p0 + t * (p1 - p0);
			const Point2<T> q1 = p1 + t * (p2 - p1);
			const Point2<T> q2 = p2 + t * (p3 - p2);

			const Point2<T> r0 = q0 + t * (q1 - q0);
			const Point2<T> r1 = q1 + t * (q2 - q1);

			const Point2<T> s0 = r0 + t * (r1 - r0);

			return {
				CubicBezierCurve2{ p0, q0, r0, s0 },
				CubicBezierCurve2{ s0, r1, q2, p3 }
			};
		}
	};
}