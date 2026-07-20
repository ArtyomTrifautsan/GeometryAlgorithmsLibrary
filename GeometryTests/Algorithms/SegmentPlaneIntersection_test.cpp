#include <gtest/gtest.h>

#include <GeometryCore/Algorithms/SegmentPlaneIntersection3.h>
#include <GeometryCore/Math/Constants.h>

using namespace Geometry;

Plane3<double> MakePlaneZ0()
{
    return Plane3<double>{ Point3<double>(0.0, 0.0, 0.0), Vector3<double>(0.0, 0.0, 1.0) };
}

TEST(SegmentPlaneIntersection3D, NormalIntersection)
{
    Plane3<double> plane = MakePlaneZ0();
    Segment3<double> seg(Point3<double>(-1.0, 0.0, -1.0), Point3<double>(1.0, 0.0, 1.0));

    auto res = Intersect(seg, plane);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.point.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(res.point.y, 0.0, EPSILON<double>);
    EXPECT_NEAR(res.point.z, 0.0, EPSILON<double>);
}

TEST(SegmentPlaneIntersection3D, IntersectionAtNonOrigin)
{
    Plane3<double> plane{ Point3<double>(5.0, 5.0, 0.0), Vector3<double>(0.0, 0.0, 1.0) };
    Segment3<double> seg(Point3<double>(5.0, 5.0, -2.0), Point3<double>(5.0, 5.0, 3.0));

    auto res = Intersect(seg, plane);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.point.z, 0.0, EPSILON<double>);
}

TEST(SegmentPlaneIntersection3D, NoIntersectionSameSide)
{
    Plane3<double> plane = MakePlaneZ0();
    Segment3<double> seg(Point3<double>(0.0, 0.0, 1.0), Point3<double>(1.0, 0.0, 2.0));

    auto res = Intersect(seg, plane);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
}

TEST(SegmentPlaneIntersection3D, ParallelButNotOnPlane)
{
    Plane3<double> plane = MakePlaneZ0();
    Segment3<double> seg(Point3<double>(0.0, 0.0, 5.0), Point3<double>(1.0, 0.0, 5.0));

    auto res = Intersect(seg, plane);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
}

TEST(SegmentPlaneIntersection3D, LiesOnPlane)
{
    Plane3<double> plane = MakePlaneZ0();
    Segment3<double> seg(Point3<double>(-1.0, 2.0, 0.0), Point3<double>(3.0, 4.0, 0.0));

    auto res = Intersect(seg, plane);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Segment);
    EXPECT_NEAR(res.overlap_segment.start.x, -1.0, EPSILON<double>);
    EXPECT_NEAR(res.overlap_segment.start.y, 2.0, EPSILON<double>);
    EXPECT_NEAR(res.overlap_segment.start.z, 0.0, EPSILON<double>);
    EXPECT_NEAR(res.overlap_segment.end.x, 3.0, EPSILON<double>);
    EXPECT_NEAR(res.overlap_segment.end.y, 4.0, EPSILON<double>);
    EXPECT_NEAR(res.overlap_segment.end.z, 0.0, EPSILON<double>);
}

TEST(SegmentPlaneIntersection3D, StartPointOnPlane)
{
    Plane3<double> plane = MakePlaneZ0();
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(1.0, 0.0, 1.0));

    auto res = Intersect(seg, plane);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.point.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(res.point.z, 0.0, EPSILON<double>);
}

TEST(SegmentPlaneIntersection3D, EndPointOnPlane)
{
    Plane3<double> plane = MakePlaneZ0();
    Segment3<double> seg(Point3<double>(1.0, 0.0, 1.0), Point3<double>(0.0, 0.0, 0.0));

    auto res = Intersect(seg, plane);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.point.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(res.point.z, 0.0, EPSILON<double>);
}

TEST(SegmentPlaneIntersection3D, DegenerateSegmentOnPlane)
{
    Plane3<double> plane = MakePlaneZ0();
    Segment3<double> seg(Point3<double>(2.0, 3.0, 0.0), Point3<double>(2.0, 3.0, 0.0));

    auto res = Intersect(seg, plane);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.point.x, 2.0, EPSILON<double>);
}

TEST(SegmentPlaneIntersection3D, DegenerateSegmentNotOnPlane)
{
    Plane3<double> plane = MakePlaneZ0();
    Segment3<double> seg(Point3<double>(2.0, 3.0, 5.0), Point3<double>(2.0, 3.0, 5.0));

    auto res = Intersect(seg, plane);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
}

TEST(SegmentPlaneIntersection3D, VerySmallSegmentCrossingPlane)
{
    Plane3<double> plane = MakePlaneZ0();
    Segment3<double> seg(Point3<double>(0.0, 0.0, -EPSILON<double> * 10), Point3<double>(0.0, 0.0, EPSILON<double> * 10));

    auto res = Intersect(seg, plane);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.point.z, 0.0, EPSILON<double>);
}

TEST(SegmentPlaneIntersection3D, AlmostParallelButIntersecting)
{
    Plane3<double> plane = MakePlaneZ0();
    Segment3<double> seg(Point3<double>(0.0, 0.0, -1e-5), Point3<double>(1.0, 0.0, 1e-5));

    auto res = Intersect(seg, plane);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.point.x, 0.5, EPSILON<double>);
}

TEST(SegmentPlaneIntersection3D, LargeCoordinates)
{
    Plane3<double> plane{ Point3<double>(0.0, 0.0, 0.0), Vector3<double>(0.0, 0.0, 1.0) };
    Segment3<double> seg(Point3<double>(0.0, 0.0, -1e6), Point3<double>(0.0, 0.0, 1e6));

    auto res = Intersect(seg, plane);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.point.z, 0.0, EPSILON<double>);
}

TEST(SegmentPlaneIntersection3D, IntersectionJustOutsideSegment)
{
    Plane3<double> plane = MakePlaneZ0();
    Segment3<double> seg(Point3<double>(0.0, 0.0, -1.0), Point3<double>(1.0, 0.0, -0.0001));

    auto res = Intersect(seg, plane);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
}