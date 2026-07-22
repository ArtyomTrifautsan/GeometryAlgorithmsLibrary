#pragma once

#include <vector>
#include <memory>

#include <GeometryCore/Primitives/Segment2.h>
#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/Primitives/Vector2.h>
#include <GeometryCore/Algorithms/SegmentSegmentIntersection2.h>
#include <GeometryCore/Algorithms/IntersectionTypes.h>
#include <GeometryCore/BoundingVolumes/AABB2.h>


namespace Geometry
{
	template <typename T>
	struct Polygon2
	{
		std::vector<Point2<T>> vertices{};
        AABB2<T> bounds{};

		Polygon2() = default;
		Polygon2(std::vector<Point2<T>> vertices_) : vertices{ std::move(vertices_) }
        {
            UpdateBounds();
        }

		[[nodiscard]] Segment2<T> GetEdge(size_t index) const noexcept
		{
			size_t len = vertices.size();
			return Segment2<T>{vertices[index], vertices[(index + 1) % len]};
		}

		[[nodiscard]] bool Valid() const noexcept
		{
			if (vertices.size() < 3)
			{
				return false;
			}

			return AllEdgesAreValid();
		}

        void UpdateBounds() noexcept
        {
            if (vertices.empty())
            {
                bounds = AABB2<T>{};
                return;
            }

            Point2<T> min = vertices[0];
            Point2<T> max = vertices[0];

            for (const auto& v : vertices)
            {
                min.x = std::min(min.x, v.x);
                min.y = std::min(min.y, v.y);
                max.x = std::max(max.x, v.x);
                max.y = std::max(max.y, v.y);
            }

            bounds = AABB2<T>{ min, max };
        }

        [[nodiscard]] const AABB2<T>& GetBounds() const noexcept
        {
            return bounds;
        }

	private:
        [[nodiscard]] bool AllEdgesAreValid() const noexcept
        {
            size_t len = vertices.size();

            for (size_t i = 0; i < len; ++i)
            {
                Segment2<T> edgeI = GetEdge(i);

                if (edgeI.IsDegenerate())
                {
                    return false;
                }

                for (size_t j = i + 1; j < len; ++j)
                {
                    Segment2<T> edgeJ = GetEdge(j);

                    auto intersectionInfo = Intersect(edgeI, edgeJ);

                    if (intersectionInfo)
                    {
                        bool areAdjacent = (j == i + 1) || (i == 0 && j == len - 1);

                        if (!areAdjacent)
                        {
                            return false;
                        }

                        if (intersectionInfo.type == IntersectionType::Segment)
                        {
                            return false;
                        }
                    }
                }
            }

            return true;
        }
	};
}