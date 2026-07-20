#pragma once

#include <GeometryCore/Primitives/Point3.h>
#include <GeometryCore/Primitives/Vector3.h>


namespace Geometry
{
	template <typename T>
	struct Ray3
	{
		Point3<T> origin;
		Vector3<T> direction;

		constexpr Ray3() = default;
		constexpr Ray3(const Point3<T>& p, const Vector3<T>& v) noexcept : origin{ p }, direction{ v } {}
	};
}