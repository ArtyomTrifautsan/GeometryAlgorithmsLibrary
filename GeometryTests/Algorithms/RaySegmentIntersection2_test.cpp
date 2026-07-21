#include <gtest/gtest.h>

#include <GeometryCore/Algorithms/RaySegmentIntersection2.h>
#include <GeometryCore/Math/Constants.h>

using namespace Geometry;


TEST(RaySegmentIntersection2D, NormalIntersection)
{
    Ray2<double> ray(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 0.0));
    Segment2<double> seg(Point2<double>(1.0, -1.0), Point2<double>(1.0, 1.0));

    auto result = Intersect(ray, seg);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(RaySegmentIntersection2D, IntersectionAtRayOrigin)
{
    Ray2<double> ray(Point2<double>(1.0, 0.0), Vector2<double>(1.0, 0.0));
    Segment2<double> seg(Point2<double>(1.0, -1.0), Point2<double>(1.0, 1.0));

    auto result = Intersect(ray, seg);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(RaySegmentIntersection2D, IntersectionAtSegmentEndpoint)
{
    Ray2<double> ray(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 1.0));
    Segment2<double> seg(Point2<double>(2.0, 2.0), Point2<double>(3.0, 1.0));

    auto result = Intersect(ray, seg);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 2.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 2.0, EPSILON<double>);
}

TEST(RaySegmentIntersection2D, NoIntersectionBehindRay)
{
    Ray2<double> ray(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 0.0));
    Segment2<double> seg(Point2<double>(-1.0, -1.0), Point2<double>(-1.0, 1.0));

    auto result = Intersect(ray, seg);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(RaySegmentIntersection2D, NoIntersectionParallel)
{
    Ray2<double> ray(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 0.0));
    Segment2<double> seg(Point2<double>(0.0, 1.0), Point2<double>(2.0, 1.0));

    auto result = Intersect(ray, seg);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(RaySegmentIntersection2D, CollinearSegmentFullyOnRay)
{
    Ray2<double> ray(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 0.0));
    Segment2<double> seg(Point2<double>(1.0, 0.0), Point2<double>(3.0, 0.0));

    auto result = Intersect(ray, seg);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Segment);
    EXPECT_NEAR(result.segment.start.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.end.x, 3.0, EPSILON<double>);
}

TEST(RaySegmentIntersection2D, CollinearSegmentPartiallyOnRay)
{
    Ray2<double> ray(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 0.0));
    Segment2<double> seg(Point2<double>(-1.0, 0.0), Point2<double>(2.0, 0.0));

    auto result = Intersect(ray, seg);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Segment);
    EXPECT_NEAR(result.segment.start.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.end.x, 2.0, EPSILON<double>);
}

TEST(RaySegmentIntersection2D, CollinearSegmentFullyBehindRay)
{
    Ray2<double> ray(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 0.0));
    Segment2<double> seg(Point2<double>(-3.0, 0.0), Point2<double>(-1.0, 0.0));

    auto result = Intersect(ray, seg);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(RaySegmentIntersection2D, CollinearSegmentStartsAtRayOrigin)
{
    Ray2<double> ray(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 0.0));
    Segment2<double> seg(Point2<double>(0.0, 0.0), Point2<double>(2.0, 0.0));

    auto result = Intersect(ray, seg);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Segment);
    EXPECT_NEAR(result.segment.start.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.end.x, 2.0, EPSILON<double>);
}

TEST(RaySegmentIntersection2D, DegenerateRay_PointOnSegment)
{
    Ray2<double> ray(Point2<double>(1.0, 0.0), Vector2<double>(0.0, 0.0));
    Segment2<double> seg(Point2<double>(0.0, 0.0), Point2<double>(2.0, 0.0));

    auto result = Intersect(ray, seg);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
}

TEST(RaySegmentIntersection2D, DegenerateRay_PointOffSegment)
{
    Ray2<double> ray(Point2<double>(3.0, 0.0), Vector2<double>(0.0, 0.0));
    Segment2<double> seg(Point2<double>(0.0, 0.0), Point2<double>(2.0, 0.0));

    auto result = Intersect(ray, seg);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(RaySegmentIntersection2D, DegenerateSegment_PointOnRay)
{
    Ray2<double> ray(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 0.0));
    Segment2<double> seg(Point2<double>(1.0, 0.0), Point2<double>(1.0, 0.0));

    auto result = Intersect(ray, seg);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
}

TEST(RaySegmentIntersection2D, DegenerateSegment_PointOffRay)
{
    Ray2<double> ray(Point2<double>(0.0, 0.0), Vector2<double>(1.0, 0.0));
    Segment2<double> seg(Point2<double>(-1.0, 0.0), Point2<double>(-1.0, 0.0));

    auto result = Intersect(ray, seg);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(RaySegmentIntersection2D, BothDegenerateSamePoint)
{
    Ray2<double> ray(Point2<double>(1.0, 1.0), Vector2<double>(0.0, 0.0));
    Segment2<double> seg(Point2<double>(1.0, 1.0), Point2<double>(1.0, 1.0));

    auto result = Intersect(ray, seg);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 1.0, EPSILON<double>);
}

TEST(RaySegmentIntersection2D, BothDegenerateDifferentPoints)
{
    Ray2<double> ray(Point2<double>(1.0, 1.0), Vector2<double>(0.0, 0.0));
    Segment2<double> seg(Point2<double>(2.0, 2.0), Point2<double>(2.0, 2.0));

    auto result = Intersect(ray, seg);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(RaySegmentIntersection2D, VerySmallCoordinates)
{
    Ray2<double> ray(Point2<double>(0.0, 0.0), Vector2<double>(EPSILON<double> *1.2, 0.0));
    Segment2<double> seg(Point2<double>(EPSILON<double> *1.1, -EPSILON<double> *1.1), Point2<double>(EPSILON<double> *1.1, EPSILON<double> *1.1));

    auto result = Intersect(ray, seg);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, EPSILON<double> *1.1, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(RaySegmentIntersection2D, VeryLargeCoordinates)
{
    Ray2<double> ray(Point2<double>(0.0, 0.0), Vector2<double>(1e6, 0.0));
    Segment2<double> seg(Point2<double>(5e5, -1e6), Point2<double>(5e5, 1e6));

    auto result = Intersect(ray, seg);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 5e5, 1e-3);
    EXPECT_NEAR(result.point.y, 0.0, 1e-3);
}