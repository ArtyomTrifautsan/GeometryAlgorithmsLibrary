#include <gtest/gtest.h>

#include <GeometryCore/Algorithms/PointPointDistance3.h>
#include <GeometryCore/Math/Constants.h>

using namespace Geometry;


TEST(PointPointDistance3D, PointsOnXAxis)
{
    Point3<double> p1(0.0, 0.0, 0.0);
    Point3<double> p2(5.0, 0.0, 0.0);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 5.0, EPSILON<double>);
}

TEST(PointPointDistance3D, PointsOnYAxis)
{
    Point3<double> p1(0.0, 0.0, 0.0);
    Point3<double> p2(0.0, 3.0, 0.0);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 3.0, EPSILON<double>);
}

TEST(PointPointDistance3D, PointsOnZAxis)
{
    Point3<double> p1(0.0, 0.0, 0.0);
    Point3<double> p2(0.0, 0.0, 4.0);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 4.0, EPSILON<double>);
}

TEST(PointPointDistance3D, PythagoreanTriangle)
{
    Point3<double> p1(0.0, 0.0, 0.0);
    Point3<double> p2(3.0, 4.0, 0.0);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 5.0, EPSILON<double>);
}

TEST(PointPointDistance3D, CubeDiagonal)
{
    Point3<double> p1(0.0, 0.0, 0.0);
    Point3<double> p2(1.0, 1.0, 1.0);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, std::sqrt(3.0), EPSILON<double>);
}

TEST(PointPointDistance3D, IdenticalPoints)
{
    Point3<double> p1(1.0, 2.0, 3.0);
    Point3<double> p2(1.0, 2.0, 3.0);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.distance, 0.0, EPSILON<double>);
}

TEST(PointPointDistance3D, IdenticalPointsAtOrigin)
{
    Point3<double> p1(0.0, 0.0, 0.0);
    Point3<double> p2(0.0, 0.0, 0.0);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.distance, 0.0, EPSILON<double>);
}

TEST(PointPointDistance3D, NegativeCoordinates)
{
    Point3<double> p1(-3.0, -4.0, 0.0);
    Point3<double> p2(0.0, 0.0, 0.0);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 5.0, EPSILON<double>);
}

TEST(PointPointDistance3D, DifferentQuadrants)
{
    Point3<double> p1(-1.0, -1.0, -1.0);
    Point3<double> p2(1.0, 1.0, 1.0);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, std::sqrt(12.0), EPSILON<double>);
}

TEST(PointPointDistance3D, VeryClosePoints)
{
    Point3<double> p1(1.0, 1.0, 1.0);
    Point3<double> p2(1.0 + EPSILON<double> * 1.8, 1.0, 1.0);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, EPSILON<double> * 1.8, EPSILON<double>);
}

TEST(PointPointDistance3D, PointsWithinTolerance)
{
    Point3<double> p1(1.0, 1.0, 1.0);
    Point3<double> p2(1.0 + EPSILON<double> * 0.5, 1.0, 1.0);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.distance, 0.0, EPSILON<double>);
}

TEST(PointPointDistance3D, VeryLargeCoordinates)
{
    Point3<double> p1(0.0, 0.0, 0.0);
    Point3<double> p2(1e6, 1e6, 1e6);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, std::sqrt(3.0) * 1e6, 1e-3);
}

TEST(PointPointDistance3D, VerySmallCoordinates)
{
    Point3<double> p1(0.0, 0.0, 0.0);
    Point3<double> p2(1e-6, 1e-6, 1e-6);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, std::sqrt(3.0) * 1e-6, 1e-12);
}

TEST(PointPointDistance3D, FractionalCoordinates)
{
    Point3<double> p1(0.5, 0.5, 0.5);
    Point3<double> p2(1.5, 1.5, 1.5);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, std::sqrt(3.0), EPSILON<double>);
}

TEST(PointPointDistance3D, MixedFractionalCoordinates)
{
    Point3<double> p1(-0.5, 0.5, -0.5);
    Point3<double> p2(0.5, -0.5, 0.5);

    auto result = Distance(p1, p2);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, std::sqrt(3.0), EPSILON<double>);
}