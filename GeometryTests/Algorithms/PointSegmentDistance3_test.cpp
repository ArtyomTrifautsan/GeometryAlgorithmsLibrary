#include <gtest/gtest.h>

#include <GeometryCore/Algorithms/PointSegmentDistance3.h>
#include <GeometryCore/Math/Constants.h>

using namespace Geometry;


TEST(PointSegmentDistance3D, PointOnMiddle)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(1.0, 0.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.distance, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, PointAtStart)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(0.0, 0.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.distance, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, PointAtEnd)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(2.0, 0.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.distance, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, PointAtQuarter)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(4.0, 0.0, 0.0));
    Point3<double> p(1.0, 0.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.distance, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, PointOnDiagonal)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 2.0, 2.0));
    Point3<double> p(1.0, 1.0, 1.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.distance, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, PointPerpendicularAboveMiddle)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(1.0, 1.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 1.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, PointPerpendicularBelowMiddle)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(1.0, -1.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 1.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, PointOffsetInZ)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(1.0, 0.0, 3.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 3.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, PointDiagonalFromSegment)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(1.0, 1.0, 1.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, std::sqrt(2.0), EPSILON<double>);
}

TEST(PointSegmentDistance3D, ProjectionBeforeStart)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(-1.0, 0.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 1.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, ProjectionAfterEnd)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(3.0, 0.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 1.0, EPSILON<double>);  // Расстояние до конца
}

TEST(PointSegmentDistance3D, ProjectionBeforeStartWithOffset)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(-1.0, 1.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, std::sqrt(2.0), EPSILON<double>);
}

TEST(PointSegmentDistance3D, ProjectionAfterEndWithOffset)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(3.0, 1.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, std::sqrt(2.0), EPSILON<double>);
}

TEST(PointSegmentDistance3D, DegenerateSegmentPointMatches)
{
    Segment3<double> seg(Point3<double>(1.0, 1.0, 1.0), Point3<double>(1.0, 1.0, 1.0));
    Point3<double> p(1.0, 1.0, 1.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.distance, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, DegenerateSegmentPointDiffers)
{
    Segment3<double> seg(Point3<double>(1.0, 1.0, 1.0), Point3<double>(1.0, 1.0, 1.0));
    Point3<double> p(2.0, 1.0, 1.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 1.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, SegmentAlongY)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(0.0, 2.0, 0.0));
    Point3<double> p(1.0, 1.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 1.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, SegmentAlongZ)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(0.0, 0.0, 2.0));
    Point3<double> p(0.0, 1.0, 1.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 1.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, VerySmallSegment)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(1e-6, 0.0, 0.0));
    Point3<double> p(0.5e-6, 1e-7, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 1e-7, 1e-12);
}

TEST(PointSegmentDistance3D, VeryLargeSegment)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(1e6, 0.0, 0.0));
    Point3<double> p(5e5, 1e3, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 1e3, 1e-3);
}

TEST(PointSegmentDistance3D, PointVeryCloseToSegment)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(1.0, EPSILON<double> * 2, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, EPSILON<double> * 2, EPSILON<double>);
}

TEST(PointSegmentDistance3D, PointWithinToleranceOfSegment)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(1.0, EPSILON<double> * 0.5, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.distance, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, SegmentWithNegativeCoordinates)
{
    Segment3<double> seg(Point3<double>(-2.0, 0.0, 0.0), Point3<double>(0.0, 0.0, 0.0));
    Point3<double> p(-1.0, 1.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 1.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, PointWithNegativeCoordinates)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(1.0, -1.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 1.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, FractionalSegmentCoordinates)
{
    Segment3<double> seg(Point3<double>(0.5, 0.5, 0.5), Point3<double>(1.5, 1.5, 1.5));
    Point3<double> p(1.0, 1.0, 1.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.distance, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, FractionalPointCoordinates)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(1.0, 0.5, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 0.5, EPSILON<double>);
}

TEST(PointSegmentDistance3D, PointCollinearButOutside)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(5.0, 0.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 3.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, ArbitraryDirectionSegment)
{
    Segment3<double> seg(Point3<double>(1.0, 2.0, 3.0), Point3<double>(4.0, 6.0, 3.0));
    Point3<double> p(2.5, 4.0, 3.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.distance, 0.0, EPSILON<double>);
}

TEST(PointSegmentDistance3D, PointFarFromSegment)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(1.0, 0.0, 0.0));
    Point3<double> p(100.0, 100.0, 100.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, std::sqrt(99.0 * 99.0 + 100.0 * 100.0 + 100.0 * 100.0), 1e-3);
}

TEST(PointSegmentDistance3, ReversedSegmentDirection)
{
    Segment3<double> seg(Point3<double>(5.0, 0.0, 0.0), Point3<double>(1.0, 0.0, 0.0));
    Point3<double> p(0.0, 0.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 1.0, EPSILON<double>);
}

TEST(PointSegmentDistance3, PointPerpendicularExactlyAtEnd)
{
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Point3<double> p(2.0, 5.0, 0.0);

    auto result = Distance(seg, p);

    EXPECT_EQ(result.type, IntersectionType::None);
    EXPECT_NEAR(result.distance, 5.0, EPSILON<double>);
}