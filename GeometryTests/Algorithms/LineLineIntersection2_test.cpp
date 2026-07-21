#include <gtest/gtest.h>

#include <GeometryCore/Algorithms/LineLineIntersection2.h>
#include <GeometryCore/Math/Constants.h>

using namespace Geometry;


TEST(LineLineIntersection2D, CrossIntersection)
{
    Line2<double> a(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 0.0));
    Line2<double> b(Point2<double>(1.0, -1.0), Vector2<double>(0.0, 1.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
    EXPECT_NEAR(result.ta, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.tb, 1.0, EPSILON<double>);
}

TEST(LineLineIntersection2D, DiagonalIntersection)
{
    Line2<double> a(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 1.0));
    Line2<double> b(Point2<double>(2.0, 0.0), Vector2<double>(-1.0, 1.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 1.0, EPSILON<double>);
}

TEST(LineLineIntersection2D, ParallelNoIntersection)
{
    Line2<double> a(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 0.0));
    Line2<double> b(Point2<double>(0.0, 1.0), Vector2<double>(1.0, 0.0));

    auto result = Intersect(a, b);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(LineLineIntersection2D, ParallelVerticalNoIntersection)
{
    Line2<double> a(Point2<double>(1.0, 0.0), Vector2<double>(0.0, 1.0));
    Line2<double> b(Point2<double>(2.0, 0.0), Vector2<double>(0.0, 1.0));

    auto result = Intersect(a, b);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(LineLineIntersection2D, CollinearSameLine)
{
    Line2<double> a(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 1.0));
    Line2<double> b(Point2<double>(2.0, 2.0), Vector2<double>(1.0, 1.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Line);
}

TEST(LineLineIntersection2D, CollinearOppositeDirections)
{
    Line2<double> a(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 0.0));
    Line2<double> b(Point2<double>(5.0, 0.0), Vector2<double>(-1.0, 0.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Line);
}

TEST(LineLineIntersection2D, DegenerateFirstLine)
{
    Line2<double> a(Point2<double>(1.0, 1.0), Vector2<double>(0.0, 0.0));
    Line2<double> b(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 0.0));

    auto result = Intersect(a, b);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(LineLineIntersection2D, BothLinesDegenerateSamePoint)
{
    Line2<double> a(Point2<double>(1.0, 1.0), Vector2<double>(0.0, 0.0));
    Line2<double> b(Point2<double>(1.0, 1.0), Vector2<double>(0.0, 0.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
}

TEST(LineLineIntersection2D, VerySmallCoordinates)
{
    Line2<double> a(Point2<double>(0.0, 0.0), Vector2<double>(EPSILON<double> *1.2, 0.0));
    Line2<double> b(Point2<double>(EPSILON<double> *1.1, -EPSILON<double> *1.1), Vector2<double>(0.0, EPSILON<double> *1.2));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, EPSILON<double> *1.1, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(LineLineIntersection2D, VeryLargeCoordinates)
{
    Line2<double> a(Point2<double>(0.0, 0.0), Vector2<double>(1e6, 0.0));
    Line2<double> b(Point2<double>(5e5, -1e6), Vector2<double>(0.0, 1e6));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 5e5, 1e-3);
    EXPECT_NEAR(result.point.y, 0.0, 1e-3);
}