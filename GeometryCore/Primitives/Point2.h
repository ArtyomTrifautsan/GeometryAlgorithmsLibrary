#pragma once

#include <GeometryCore/Primitives/Vector2.h>
#include <GeometryCore/Math/Utils.h>


namespace Geometry
{
	template <typename T>
	struct Point2
	{
		T x = 0;
		T y = 0;

		constexpr Point2() = default;
		constexpr Point2(T x_, T y_) noexcept : x{x_}, y{y_} {}

		constexpr Point2& operator+=(const Vector2<T>& v) noexcept
		{
			x += v.x;
			y += v.y;
			return *this;
		}

		constexpr Point2& operator-=(const Vector2<T>& v) noexcept
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}

		//[[nodiscard]] constexpr bool Equals(const Point2& other, T tolerance = T(1e-9)) const noexcept
		//{
		//	return (*this - other).SqrLen() <= tolerance * tolerance;
		//}
	};

	template <typename T>
	[[nodiscard]] constexpr Vector2<T> operator-(const Point2<T>& lhs, const Point2<T>& rhs) noexcept
	{
		return Vector2<T>{lhs.x - rhs.x, lhs.y - rhs.y};
	}

	template <typename T>
	[[nodiscard]] constexpr Point2<T> operator+(Point2<T> p, const Vector2<T>& v) noexcept
	{
		p += v;
		return p;
	}

	template <typename T>
	[[nodiscard]] constexpr Point2<T> operator-(Point2<T> p, const Vector2<T>& v) noexcept
	{
		p -= v;
		return p;
	}

	template <typename T>
	[[nodiscard]] constexpr bool AreEqual(const Point2<T>& lhs, const Point2<T>& rhs) noexcept
	{
		return AreEqual(lhs.x, rhs.x) && AreEqual(lhs.y, rhs.y);
	}
}