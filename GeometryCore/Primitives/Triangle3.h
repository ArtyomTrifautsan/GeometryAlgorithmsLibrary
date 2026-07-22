#pragma once

#include <GeometryCore/Primitives/Point3.h>
#include <GeometryCore/Primitives/Vector3.h>
#include <GeometryCore/Math/Utils.h>


namespace Geometry
{
	template <typename T>
	struct Triangle3
	{
		Point3<T> V0;
		Point3<T> V1;
		Point3<T> V2;

		constexpr Triangle3() = default;
		constexpr Triangle3(const Point3<T>& p1, const Point3<T>& p2, const Point3<T>& p3) noexcept
			: V0{p1}, V1{p2}, V2{p3} { }

		bool IsDegenerate() const noexcept
		{
			Vector3<T> edge1 = V1 - V0;
			Vector3<T> edge2 = V2 - V0;
			Vector3<T> edge3 = V2 - V1;

			if (edge1.Zero() && edge2.Zero() && edge3.Zero())
			{
				return true;
			}

			Vector3<T> normal = Cross(edge1, edge2);

			T max_edge1 = std::max({ Abs(edge1.x), Abs(edge1.y), Abs(edge1.z) });
			T max_edge2 = std::max({ Abs(edge2.x), Abs(edge2.y), Abs(edge2.z) });

			T geometric_tolerance = EPSILON<T> * max_edge1 * max_edge2;
			Vector3<T> roundoff_tolerance_v = CrossRoundoffTolerance(edge1, edge2);
			T roundoff_tolerance = std::max({ roundoff_tolerance_v.x, roundoff_tolerance_v.y, roundoff_tolerance_v.z });

			T D_tolerance = std::max(geometric_tolerance, roundoff_tolerance);

			return normal.Zero(D_tolerance);
		}
	};
}