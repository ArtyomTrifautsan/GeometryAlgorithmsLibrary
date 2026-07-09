#include <gtest/gtest.h>

#include <GeometryCore/Algorithms/Intersection.h>
#include <GeometryCore/Math/Constants.h>

using namespace Geometry;


// ========== Segment-Segment intersection ==========

TEST(SegmentSegmentIntersection2D, CrossIntersection)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(2.0, 0.0));
    Segment2<double> b(Point2<double>(1.0, -1.0), Point2<double>(1.0, 1.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, DiagonalSegmentsIntersect)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(2.0, 2.0));
    Segment2<double> b(Point2<double>(2.0, 0.0), Point2<double>(0.0, 2.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 1.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, ParallelNoIntersection)
{
    Segment2<double> a(Point2<double>(1.0, 1.0), Point2<double>(2.0, 3.0));
    Segment2<double> b(Point2<double>(1.0, 2.0), Point2<double>(2.0, 4.0));

    auto result = Intersect(a, b);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(SegmentSegmentIntersection2D, ParallelNoIntersectionEvenProjection)
{
    Segment2<double> a(Point2<double>(1.0, 1.0), Point2<double>(2.0, 3.0));
    Segment2<double> b(Point2<double>(5.0, 2.0), Point2<double>(6.0, 4.0));

    auto result = Intersect(a, b);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(SegmentSegmentIntersection2D, HorizontalParallelNoIntersection)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(2.0, 0.0));
    Segment2<double> b(Point2<double>(0.0, 1.0), Point2<double>(2.0, 1.0));

    auto result = Intersect(a, b);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(SegmentSegmentIntersection2D, HorizontalParallelNoIntersectionEvenProjection)
{
    Segment2<double> a(Point2<double>(5.0, 0.0), Point2<double>(7.0, 0.0));
    Segment2<double> b(Point2<double>(0.0, 1.0), Point2<double>(2.0, 1.0));

    auto result = Intersect(a, b);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(SegmentSegmentIntersection2D, VerticalParallelNoIntersection)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(0.0, 1.0));
    Segment2<double> b(Point2<double>(2.0, 0.0), Point2<double>(2.0, 1.0));

    auto result = Intersect(a, b);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(SegmentSegmentIntersection2D, VerticalParallelNoIntersectionEvenProjection)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(0.0, 3.0));
    Segment2<double> b(Point2<double>(2.0, 4.0), Point2<double>(2.0, 7.0));

    auto result = Intersect(a, b);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(SegmentSegmentIntersection2D, CollinearNoOverlap)
{
    Segment2<double> a(Point2<double>(1.0, 0.0), Point2<double>(2.0, 1.0));
    Segment2<double> b(Point2<double>(3.0, 2.0), Point2<double>(5.0, 4.0));

    auto result = Intersect(a, b);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(SegmentSegmentIntersection2D, CollinearPartialOverlap)
{
    Segment2<double> a(Point2<double>(1.0, 0.0), Point2<double>(4.0, 3.0));
    Segment2<double> b(Point2<double>(3.0, 2.0), Point2<double>(8.0, 7.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Segment);
    EXPECT_NEAR(result.segment.start.x, 3.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.start.y, 2.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.end.x, 4.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.end.y, 3.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, CollinearFullOverlapOverlap)
{
    Segment2<double> a(Point2<double>(1.0, 0.0), Point2<double>(8.0, 7.0));
    Segment2<double> b(Point2<double>(3.0, 2.0), Point2<double>(5.0, 4.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Segment);
    EXPECT_NEAR(result.segment.start.x, 3.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.start.y, 2.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.end.x, 5.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.end.y, 4.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, CollinearTouchAtEndpoint)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(1.0, 0.0));
    Segment2<double> b(Point2<double>(1.0, 0.0), Point2<double>(2.0, 0.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, SameSegments)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(2.0, 2.0));
    Segment2<double> b(Point2<double>(0.0, 0.0), Point2<double>(2.0, 2.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Segment);
    EXPECT_NEAR(result.segment.start.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.start.y, 0.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.end.x, 2.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.end.y, 2.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, HorizontalSameSegments)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(2.0, 0.0));
    Segment2<double> b(Point2<double>(0.0, 0.0), Point2<double>(2.0, 0.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Segment);
    EXPECT_NEAR(result.segment.start.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.start.y, 0.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.end.x, 2.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.end.y, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, VerticalSameSegments)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(0.0, 2.0));
    Segment2<double> b(Point2<double>(0.0, 0.0), Point2<double>(0.0, 2.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Segment);
    EXPECT_NEAR(result.segment.start.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.start.y, 0.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.end.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(result.segment.end.y, 2.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, EndSegmentIntersection)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(2.0, 0.0));
    Segment2<double> b(Point2<double>(1.0, 0.0), Point2<double>(1.0, 1.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, EndEndIntersection)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(1.0, 0.0));
    Segment2<double> b(Point2<double>(1.0, 0.0), Point2<double>(1.0, 1.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, IntersectOnlyLinesNotSegments)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(0.5, 0.0));
    Segment2<double> b(Point2<double>(1.0, -1.0), Point2<double>(1.0, 1.0));

    auto result = Intersect(a, b);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(SegmentSegmentIntersection2D, NegativeCoordinates)
{
    Segment2<double> a(Point2<double>(-2.0, -2.0), Point2<double>(2.0, 2.0));
    Segment2<double> b(Point2<double>(-2.0, 2.0), Point2<double>(2.0, -2.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, VerySmallSegments)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(EPSILON<double> * 1.2, 0.0));
    Segment2<double> b(Point2<double>(EPSILON<double> * 1.1, -EPSILON<double> * 1.1), Point2<double>(EPSILON<double> * 1.1, EPSILON<double> * 1.1));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, EPSILON<double> * 1.1, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, VeryLargeCoordinates)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(1e6, 0.0));
    Segment2<double> b(Point2<double>(5e5, -1e6), Point2<double>(5e5, 1e6));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 5e5, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, BothDegenerateSamePoint)
{
    Segment2<double> a(Point2<double>(1.0, 1.0), Point2<double>(1.0, 1.0));
    Segment2<double> b(Point2<double>(1.0, 1.0), Point2<double>(1.0, 1.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 1.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, BothDegenerateSamePointInStartCoordinateSystem)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(0.0, 0.0));
    Segment2<double> b(Point2<double>(0.0, 0.0), Point2<double>(0.0, 0.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, BothDegenerateDifferentPoints)
{
    Segment2<double> a(Point2<double>(1.0, 1.0), Point2<double>(1.0, 1.0));
    Segment2<double> b(Point2<double>(2.0, 2.0), Point2<double>(2.0, 2.0));

    auto result = Intersect(a, b);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(SegmentIntersection2D_Degenerate, BothDegenerateVeryClose)
{
    Segment2<double> a(Point2<double>(1.0, 1.0), Point2<double>(1.0, 1.0));
    Segment2<double> b(Point2<double>(1.0 + EPSILON<double> * 0.9, 1.0 + EPSILON<double> *0.9),
                        Point2<double>(1.0 + EPSILON<double> * 0.9, 1.0 + EPSILON<double> *0.9));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 1.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, FirstDegenerateOnSecond)
{
    Segment2<double> a(Point2<double>(1.0, 0.0), Point2<double>(1.0, 0.0));
    Segment2<double> b(Point2<double>(0.0, 0.0), Point2<double>(2.0, 0.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, FirstDegenerateNotOnSecond)
{
    Segment2<double> a(Point2<double>(3.0, 0.0), Point2<double>(3.0, 0.0));
    Segment2<double> b(Point2<double>(0.0, 0.0), Point2<double>(2.0, 0.0));

    auto result = Intersect(a, b);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.type, IntersectionType::None);
}

TEST(SegmentSegmentIntersection2D, SecondDegenerateOnFirst)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(2.0, 0.0));
    Segment2<double> b(Point2<double>(1.0, 0.0), Point2<double>(1.0, 0.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, SecondDegenerateOnEndpoint)
{
    Segment2<double> a(Point2<double>(0.0, 0.0), Point2<double>(2.0, 0.0));
    Segment2<double> b(Point2<double>(2.0, 0.0), Point2<double>(2.0, 0.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 2.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 0.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, DegenerateOnDiagonal)
{
    Segment2<double> a(Point2<double>(1.0, 1.0), Point2<double>(1.0, 1.0));
    Segment2<double> b(Point2<double>(0.0, 0.0), Point2<double>(2.0, 2.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, 1.0, EPSILON<double>);
}

TEST(SegmentSegmentIntersection2D, DegenerateVeryCloseToLine)
{
    Segment2<double> a(Point2<double>(1.0, EPSILON<double> * 0.1), Point2<double>(1.0, EPSILON<double> * 0.1));
    Segment2<double> b(Point2<double>(0.0, 0.0), Point2<double>(2.0, 0.0));

    auto result = Intersect(a, b);

    EXPECT_TRUE(result);
    EXPECT_EQ(result.type, IntersectionType::Point);
    EXPECT_NEAR(result.point.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(result.point.y, EPSILON<double> *0.1, EPSILON<double>);
}