#pragma once

#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/Primitives/Vector2.h>


namespace Geometry
{
	template <typename T>
	struct Line2
	{
		Point2<T> origin;
		Vector2<T> direction;

		constexpr Line2() = default;
		constexpr Line2(const Point2<T>& p, const Vector2<T>& v) noexcept : origin{ p }, direction{ v } {}

		[[nodiscard]] constexpr bool ContainsPoint(const Point2<T>& p) const noexcept
		{
			if (direction.Zero())
			{
				return AreEqual(origin, p);
			}

			Vector2<T> Vaux = p - origin;
			const Vector2<T>& V = direction;

			T roundoff_tolerance = EPSILON<T> *(Abs(V.x * Vaux.y) + Abs(Vaux.x * V.y));
			T geometric_tolerance = EPSILON<T> *std::max(Abs(V.x), Abs(V.y)) * std::max(Abs(Vaux.x), Abs(Vaux.y));
			T D_tolerance = std::max(roundoff_tolerance, geometric_tolerance);

			T D = Cross(V, Vaux);

			return IsZero(D, D_tolerance);
		}
	};
}