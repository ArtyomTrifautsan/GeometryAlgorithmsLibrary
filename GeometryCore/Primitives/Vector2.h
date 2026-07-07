#pragma once

#include <cmath>
#include <limits>
#include <exception>
#include <stdexcept>
//#include <algorithm>


namespace Geometry
{
	// t - float/double
	template <typename T>
	struct Vector2
	{
		T x = 0;
		T y = 0;

		Vector2() = default;
		Vector2(T x_, T y_) : x{x_}, y{y_} {}

		[[nodiscard]] constexpr T SqrLen() const noexcept { return x * x + y * y; }
		
		[[nodiscard]] T Len() const noexcept { return std::sqrt(SqrLen()); }

		void Normalize()
		{
			T length = Len();
			T Epsilon = 1e-9;

			if (length < Epsilon)
			{
				throw std::runtime_error("Attempt to normalize a vector with zero length");
			}

			T invLen = T(1) / length;
			x *= invLen;
			y *= invLen;
		}

		[[nodiscard]] constexpr Vector2 operator-() const noexcept { return { -x, -y }; }

		constexpr Vector2& operator+=(const Vector2& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		constexpr Vector2& operator-=(const Vector2& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		constexpr Vector2& operator*=(T scalar) noexcept {
			x *= scalar;
			y *= scalar;
			return *this;
		}
	};


	template <typename T>
	[[nodiscard]] constexpr Vector2<T> operator+(Vector2<T> lhs, const Vector2<T>& rhs) noexcept {
		lhs += rhs;
		return lhs;
	}

	template <typename T>
	[[nodiscard]] constexpr Vector2<T> operator-(Vector2<T> lhs, const Vector2<T>& rhs) noexcept {
		lhs -= rhs;
		return lhs;
	}

	template <typename T>
	[[nodiscard]] constexpr Vector2<T> operator*(Vector2<T> v, T scalar) noexcept {
		v *= scalar;
		return v;
	}

	template <typename T>
	[[nodiscard]] constexpr Vector2<T> operator*(T scalar, Vector2<T> v) noexcept {
		v *= scalar;
		return v;
	}

	template <typename T>
	[[nodiscard]] constexpr T Dot(const Vector2<T>& lhs, const Vector2<T>& rhs) noexcept {
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	template <typename T>
	[[nodiscard]] constexpr T Cross(const Vector2<T>& lhs, const Vector2<T>& rhs) noexcept {
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}
}