#include <gtest/gtest.h>

#include <GeometryCore/Algorithms/SegmentSegmentDistance3.h>
#include <GeometryCore/Math/Constants.h>

using namespace Geometry;


TEST(SegmentSegmentDistance3D, CrossIntersectionXY)
{
    Segment3<double> seg1(Point3<double>(-1.0, 0.0, 0.0), Point3<double>(1.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(0.0, -1.0, 0.0), Point3<double>(0.0, 1.0, 0.0));

    auto res = Distance(seg1, seg2);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.distance, 0.0, EPSILON<double>);
    EXPECT_NEAR(res.point1.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(res.point2.x, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, SkewSegments3D)
{
    Segment3<double> seg1(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(1.0, 1.0, 1.0), Point3<double>(1.0, 1.0, 3.0));

    auto res = Distance(seg1, seg2);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
    EXPECT_NEAR(res.distance, std::sqrt(2.0), EPSILON<double>);

    EXPECT_NEAR(res.point1.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(res.point1.y, 0.0, EPSILON<double>);
    EXPECT_NEAR(res.point1.z, 0.0, EPSILON<double>);

    EXPECT_NEAR(res.point2.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(res.point2.y, 1.0, EPSILON<double>);
    EXPECT_NEAR(res.point2.z, 1.0, EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, TouchAtEndpoints)
{
    Segment3<double> seg1(Point3<double>(0.0, 0.0, 0.0), Point3<double>(1.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(1.0, 0.0, 0.0), Point3<double>(1.0, 1.0, 0.0));

    auto res = Distance(seg1, seg2);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.distance, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, CollinearFullOverlap)
{
    Segment3<double> seg1(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));

    auto res = Distance(seg1, seg2);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Segment);
    EXPECT_NEAR(res.distance, 0.0, EPSILON<double>);
    EXPECT_NEAR(res.segment.start.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(res.segment.end.x, 2.0, EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, CollinearPartialOverlap)
{
    Segment3<double> seg1(Point3<double>(0.0, 0.0, 0.0), Point3<double>(3.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(2.0, 0.0, 0.0), Point3<double>(5.0, 0.0, 0.0));

    auto res = Distance(seg1, seg2);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Segment);
    EXPECT_NEAR(res.distance, 0.0, EPSILON<double>);
    EXPECT_NEAR(res.segment.start.x, 2.0, EPSILON<double>);
    EXPECT_NEAR(res.segment.end.x, 3.0, EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, CollinearTouchAtEndpoint)
{
    Segment3<double> seg1(Point3<double>(0.0, 0.0, 0.0), Point3<double>(1.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(1.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));

    auto res = Distance(seg1, seg2);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.distance, 0.0, EPSILON<double>);
    EXPECT_NEAR(res.point1.x, 1.0, EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, CollinearDisjoint)
{
    Segment3<double> seg1(Point3<double>(0.0, 0.0, 0.0), Point3<double>(1.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(2.0, 0.0, 0.0), Point3<double>(3.0, 0.0, 0.0));

    auto res = Distance(seg1, seg2);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
    EXPECT_NEAR(res.distance, 1.0, EPSILON<double>);
    EXPECT_NEAR(res.point1.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(res.point2.x, 2.0, EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, ParallelNonCollinearSamePlane)
{
    Segment3<double> seg1(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(0.0, 1.0, 0.0), Point3<double>(2.0, 1.0, 0.0));

    auto res = Distance(seg1, seg2);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
    EXPECT_NEAR(res.distance, 1.0, EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, ParallelNonCollinearOffsetZ)
{
    Segment3<double> seg1(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(3.0, 0.0, 1.0), Point3<double>(5.0, 0.0, 1.0));

    auto res = Distance(seg1, seg2);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
    EXPECT_NEAR(res.distance, std::sqrt(1.0 + 1.0), EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, BothDegenerateSamePoint)
{
    Segment3<double> seg1(Point3<double>(1.0, 2.0, 3.0), Point3<double>(1.0, 2.0, 3.0));
    Segment3<double> seg2(Point3<double>(1.0, 2.0, 3.0), Point3<double>(1.0, 2.0, 3.0));

    auto res = Distance(seg1, seg2);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.distance, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, BothDegenerateDifferentPoints)
{
    Segment3<double> seg1(Point3<double>(0.0, 0.0, 0.0), Point3<double>(0.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(3.0, 4.0, 0.0), Point3<double>(3.0, 4.0, 0.0));

    auto res = Distance(seg1, seg2);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
    EXPECT_NEAR(res.distance, 5.0, EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, FirstDegeneratePointOnSegment)
{
    Segment3<double> seg1(Point3<double>(1.0, 0.0, 0.0), Point3<double>(1.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));

    auto res = Distance(seg1, seg2);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.distance, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, SecondDegeneratePointOffSegmentProjectionInside)
{
    Segment3<double> seg1(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(1.0, 1.0, 0.0), Point3<double>(1.0, 1.0, 0.0));

    auto res = Distance(seg1, seg2);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
    EXPECT_NEAR(res.distance, 1.0, EPSILON<double>);
    EXPECT_NEAR(res.point1.x, 1.0, EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, SecondDegeneratePointOffSegmentProjectionOutside)
{
    Segment3<double> seg1(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(3.0, 1.0, 0.0), Point3<double>(3.0, 1.0, 0.0));

    auto res = Distance(seg1, seg2);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
    EXPECT_NEAR(res.distance, std::sqrt(1.0 + 1.0), EPSILON<double>);
    EXPECT_NEAR(res.point1.x, 2.0, EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, DistanceWithinAdaptiveTolerance)
{
    Segment3<double> seg1(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(1.0, EPSILON<double> *0.5, 0.0), Point3<double>(1.0, 2.0, 0.0));

    auto res = Distance(seg1, seg2);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
}

TEST(SegmentSegmentDistance3D, ProjectionExactlyOnEndpoint)
{
    Segment3<double> seg1(Point3<double>(0.0, 0.0, 0.0), Point3<double>(1.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(1.0, 1.0, 0.0), Point3<double>(1.0, 2.0, 0.0));

    auto res = Distance(seg1, seg2);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
    EXPECT_NEAR(res.distance, 1.0, EPSILON<double>);
    EXPECT_NEAR(res.point1.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(res.point2.y, 1.0, EPSILON<double>);
}

TEST(SegmentSegmentDistance3D, CollinearWithNegativeCoordinates)
{
    Segment3<double> seg1(Point3<double>(-3.0, 0.0, 0.0), Point3<double>(-1.0, 0.0, 0.0));
    Segment3<double> seg2(Point3<double>(-2.0, 0.0, 0.0), Point3<double>(0.0, 0.0, 0.0));

    auto res = Distance(seg1, seg2);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Segment);
    EXPECT_NEAR(res.segment.start.x, -2.0, EPSILON<double>);
    EXPECT_NEAR(res.segment.end.x, -1.0, EPSILON<double>);
}