#pragma once

#include <cmath>

#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/Primitives/Vector2.h>
#include <GeometryCore/Math/Utils.h>
#include <GeometryCore/Math/Constants.h>


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

		[[nodiscard]] constexpr Point2<T> PointAt(T t) const noexcept
		{
			return start + Vector() * t;
		}

		[[nodiscard]] constexpr bool IsDegenerate() const noexcept
		{
			return AreEqual(start, end);
		}

		[[nodiscard]] constexpr bool ContainsPoint(const Point2<T>& p) const noexcept
		{
			if (IsDegenerate())
			{
				return AreEqual(start, p);
			}

			Vector2<T> Vaux = p - start;
			Vector2<T> V = Vector();

			T roundoff_tolerance = EPSILON<T> *(Abs(V.x * Vaux.y) + Abs(Vaux.x * V.y));
			T geometric_tolerance = EPSILON<T> *std::max(Abs(V.x), Abs(V.y)); // ≈ EPSILON * |V|
			T D_tolerance = std::max(roundoff_tolerance, geometric_tolerance);
			

			T D = Cross(V, Vaux);
			//T D_tolerance = EPSILON<T> * (Abs(V.x * Vaux.y) + Abs(Vaux.x * V.y));

			if (!IsZero(D, D_tolerance))
			{
				return false;
			}

			T dotVV = Dot(V, V);
			T dotVVaux = Dot(V, Vaux);
			T dot_tolerance = EPSILON<T> * dotVV;

			return IsGreaterOrEqual(dotVVaux, T(0), dot_tolerance) && IsLessOrEqual(dotVVaux, dotVV, dot_tolerance);
		}
	};
}