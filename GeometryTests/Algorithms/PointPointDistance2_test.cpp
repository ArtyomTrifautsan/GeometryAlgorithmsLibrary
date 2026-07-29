#include <gtest/gtest.h>
#include <GeometryCore/Algorithms/PointPointDistance2.h>
#include <GeometryCore/Math/Constants.h>

using namespace Geometry;

TEST(PointPointDistance2D, SamePoints)
{
    Point2<double> p1(1.5, 2.5);
    Point2<double> p2(1.5, 2.5);
    auto res = Distance(p1, p2);

    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.distance, 0.0, EPSILON<double>);
}

TEST(PointPointDistance2D, DifferentPoints)
{
    Point2<double> p1(0.0, 0.0);
    Point2<double> p2(3.0, 4.0);
    auto res = Distance(p1, p2);

    EXPECT_EQ(res.type, IntersectionType::None);
    EXPECT_NEAR(res.distance, 5.0, EPSILON<double>);
}

TEST(PointPointDistance2D, NegativeCoordinates)
{
    Point2<double> p1(-3.0, -4.0);
    Point2<double> p2(0.0, 0.0);
    auto res = Distance(p1, p2);

    EXPECT_EQ(res.type, IntersectionType::None);
    EXPECT_NEAR(res.distance, 5.0, EPSILON<double>);
}