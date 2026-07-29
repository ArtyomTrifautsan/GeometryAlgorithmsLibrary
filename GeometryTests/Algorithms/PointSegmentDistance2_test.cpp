#include <gtest/gtest.h>
#include <GeometryCore/Algorithms/PointSegmentDistance2.h>
#include <GeometryCore/Math/Constants.h>

using namespace Geometry;

TEST(PointSegmentDistance2D, PointOnSegment_Middle)
{
    Segment2<double> seg(Point2<double>(0.0, 0.0), Point2<double>(4.0, 0.0));
    Point2<double> p(2.0, 0.0);

    auto res = Distance(p, seg);

    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.distance, 0.0, EPSILON<double>);
    EXPECT_NEAR(res.closest_point.x, 2.0, EPSILON<double>);
}

TEST(PointSegmentDistance2D, PointOnSegment_Start)
{
    Segment2<double> seg(Point2<double>(1.0, 1.0), Point2<double>(3.0, 3.0));
    Point2<double> p(1.0, 1.0);

    auto res = Distance(p, seg);

    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.distance, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance2D, PointOnSegment_End)
{
    Segment2<double> seg(Point2<double>(1.0, 1.0), Point2<double>(3.0, 3.0));
    Point2<double> p(3.0, 3.0);

    auto res = Distance(p, seg);

    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.distance, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance2D, PointOutside_ProjectionInside)
{
    Segment2<double> seg(Point2<double>(0.0, 0.0), Point2<double>(4.0, 0.0));
    Point2<double> p(2.0, 3.0);

    auto res = Distance(p, seg);

    EXPECT_EQ(res.type, IntersectionType::None);
    EXPECT_NEAR(res.distance, 3.0, EPSILON<double>);
    EXPECT_NEAR(res.closest_point.x, 2.0, EPSILON<double>);
    EXPECT_NEAR(res.closest_point.y, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance2D, PointOutside_ProjectionBeforeStart)
{
    Segment2<double> seg(Point2<double>(0.0, 0.0), Point2<double>(4.0, 0.0));
    Point2<double> p(-2.0, 3.0);

    auto res = Distance(p, seg);

    EXPECT_EQ(res.type, IntersectionType::None);
    EXPECT_NEAR(res.distance, std::sqrt(13.0), EPSILON<double>);
    EXPECT_NEAR(res.closest_point.x, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance2D, PointOutside_ProjectionAfterEnd)
{
    Segment2<double> seg(Point2<double>(0.0, 0.0), Point2<double>(4.0, 0.0));
    Point2<double> p(6.0, 3.0);

    auto res = Distance(p, seg);

    EXPECT_EQ(res.type, IntersectionType::None);
    EXPECT_NEAR(res.distance, std::sqrt(13.0), EPSILON<double>);
    EXPECT_NEAR(res.closest_point.x, 4.0, EPSILON<double>);
}

TEST(PointSegmentDistance2D, DegenerateSegment_PointMatches)
{
    Segment2<double> seg(Point2<double>(2.0, 2.0), Point2<double>(2.0, 2.0));
    Point2<double> p(2.0, 2.0);

    auto res = Distance(p, seg);

    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.distance, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance2D, DegenerateSegment_PointDiffers)
{
    Segment2<double> seg(Point2<double>(2.0, 2.0), Point2<double>(2.0, 2.0));
    Point2<double> p(5.0, 6.0);

    auto res = Distance(p, seg);

    EXPECT_EQ(res.type, IntersectionType::None);
    EXPECT_NEAR(res.distance, 5.0, EPSILON<double>);
}

TEST(PointSegmentDistance2D, NumericalStability_VeryCloseToSegment)
{
    Segment2<double> seg(Point2<double>(0.0, 0.0), Point2<double>(2.0, 0.0));
    Point2<double> p(1.0, EPSILON<double> *0.5);

    auto res = Distance(p, seg);

    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.distance, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance2D, DiagonalSegment)
{
    Segment2<double> seg(Point2<double>(0.0, 0.0), Point2<double>(3.0, 4.0));
    Point2<double> p(1.5, 2.0);

    auto res = Distance(p, seg);

    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.distance, 0.0, EPSILON<double>);
}