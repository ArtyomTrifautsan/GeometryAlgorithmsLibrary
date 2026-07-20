#pragma once

#include <GeometryCore/Primitives/Point3.h>
#include <GeometryCore/Primitives/Vector3.h>


namespace Geometry
{
	template <typename T>
	struct Plane3
	{
		Point3<T> origin;
		Vector3<T> normal;
		constexpr Plane3() = default;
		constexpr Plane3(const Point3<T>& p, const Vector3<T>& n) noexcept : origin{ p }, normal{ n } {}
	};
}