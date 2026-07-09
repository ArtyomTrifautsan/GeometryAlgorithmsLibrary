#pragma once

#include <cmath>
#include <limits>
#include <exception>
#include <stdexcept>

#include <GeometryCore/Math/Utils.h>
#include <GeometryCore/Math/Constants.h>


namespace Geometry
{
	// T - float/double
	template <typename T>
	struct Vector3
	{
		T x = 0;
		T y = 0;
		T z = 0;

		constexpr Vector3() = default;
		constexpr Vector3(T x_, T y_, T z_) : x{ x_ }, y{ y_ }, z{ z_ } {}

		[[nodiscard]] constexpr T SqrLen() const noexcept { return x * x + y * y + z * z; }

		[[nodiscard]] T Len() const noexcept { return std::sqrt(SqrLen()); }

		bool Normalize()
		{
			T length = Len();

			if (length < EPSILON<T>)
			{
				return false;
			}

			T invLen = T(1) / length;
			x *= invLen;
			y *= invLen;
			z *= invLen;

			return true;
		}

		[[nodiscard]] constexpr Vector3 operator-() const noexcept { return { -x, -y, -z }; }

		constexpr Vector3& operator+=(const Vector3& other) noexcept
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		constexpr Vector3& operator-=(const Vector3& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		constexpr Vector3& operator*=(T scalar) noexcept
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}
	};

	template <typename T>
	[[nodiscard]] constexpr Vector3<T> operator+(Vector3<T> lhs, const Vector3<T>& rhs) noexcept
	{
		lhs += rhs;
		return lhs;
	}

	template <typename T>
	[[nodiscard]] constexpr Vector3<T> operator-(Vector3<T> lhs, const Vector3<T>& rhs) noexcept
	{
		lhs -= rhs;
		return lhs;
	}

	template <typename T>
	[[nodiscard]] constexpr Vector3<T> operator*(Vector3<T> v, T scalar) noexcept
	{
		v *= scalar;
		return v;
	}

	template <typename T>
	[[nodiscard]] constexpr Vector3<T> operator*(T scalar, Vector3<T> v) noexcept
	{
		v *= scalar;
		return v;
	}

	template <typename T>
	[[nodiscard]] constexpr T Dot(const Vector3<T>& lhs, const Vector3<T>& rhs) noexcept
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	template <typename T>
	[[nodiscard]] constexpr Vector3<T> Cross(const Vector3<T>& lhs, const Vector3<T>& rhs) noexcept
	{
		return {
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		};
	}

	template <typename T>
	[[nodiscard]] constexpr bool AreEqual(const Vector3<T>& lhs, const Vector3<T>& rhs) noexcept
	{
		return AreEqual(lhs.x, rhs.x) && AreEqual(lhs.y, rhs.y) && AreEqual(lhs.z, rhs.z);
	}
}