#include <gtest/gtest.h>
#include <GeometryCore/BoundingVolumes/AABB2.h>

using namespace Geometry;

TEST(AABB2Test, Contains_PointInside)
{
    AABB2<double> box(Point2<double>(0.0, 0.0), Point2<double>(2.0, 2.0));
    Point2<double> point(1.0, 1.0);

    EXPECT_TRUE(box.Contains(point));
}

TEST(AABB2Test, Contains_PointOutside)
{
    AABB2<double> box(Point2<double>(0.0, 0.0), Point2<double>(2.0, 2.0));
    Point2<double> point(3.0, 3.0);

    EXPECT_FALSE(box.Contains(point));
}

TEST(AABB2Test, Contains_PointOnBoundary)
{
    AABB2<double> box(Point2<double>(0.0, 0.0), Point2<double>(2.0, 2.0));
    Point2<double> point(0.0, 1.0);

    EXPECT_TRUE(box.Contains(point));
}