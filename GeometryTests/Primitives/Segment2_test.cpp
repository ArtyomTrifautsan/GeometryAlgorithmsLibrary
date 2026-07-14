#include "gtest/gtest.h"
#include <GeometryCore/Primitives/Segment2.h>
#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/Primitives/Vector2.h>

using namespace Geometry;

TEST(Segment2Test, DefaultConstructor) {
    Segment2<double> seg;
    EXPECT_DOUBLE_EQ(seg.start.x, 0.0);
    EXPECT_DOUBLE_EQ(seg.start.y, 0.0);
    EXPECT_DOUBLE_EQ(seg.end.x, 0.0);
    EXPECT_DOUBLE_EQ(seg.end.y, 0.0);
}

TEST(Segment2Test, ParamentrizedConstructor) {
    Segment2<double> seg{ Point2<double>{1.0, -1.0}, Point2<double>{3.0, 4.0} };
    EXPECT_DOUBLE_EQ(seg.start.x, 1.0);
    EXPECT_DOUBLE_EQ(seg.start.y, -1.0);
    EXPECT_DOUBLE_EQ(seg.end.x, 3.0);
    EXPECT_DOUBLE_EQ(seg.end.y, 4.0);
}

TEST(Segment2Test, VectorMethod) {
    Segment2<double> seg(Point2<double>(1.0, 2.0), Point2<double>(4.0, 6.0));
    auto v = seg.Vector();
    EXPECT_DOUBLE_EQ(v.x, 3.0);
    EXPECT_DOUBLE_EQ(v.y, 4.0);
}

TEST(Segment2Test, SqrLength) {
    Segment2<double> seg(Point2<double>(0.0, 0.0), Point2<double>(3.0, 4.0));
    EXPECT_DOUBLE_EQ(seg.SqrLength(), 25.0);
}

TEST(Segment2Test, Length) {
    Segment2<double> seg(Point2<double>(0.0, 0.0), Point2<double>(3.0, 4.0));
    EXPECT_DOUBLE_EQ(seg.Length(), 5.0);
}

TEST(Segment2Test, MidpointCalculation) {
    Segment2<double> seg(Point2<double>(-2.0, 4.0), Point2<double>(4.0, 0.0));
    auto mid = seg.Midpoint();

    EXPECT_DOUBLE_EQ(mid.x, 1.0);
    EXPECT_DOUBLE_EQ(mid.y, 2.0);
}

TEST(Segment2Test, PointAtCalculation) {
    Segment2<double> seg(Point2<double>(1.0, 2.0), Point2<double>(5.0, 10.0));
    auto point_at_ = seg.PointAt(0.25);

    EXPECT_DOUBLE_EQ(point_at_.x, 2.0);
    EXPECT_DOUBLE_EQ(point_at_.y, 4.0);
}

TEST(Segment2Test, IsDegenerateSamePoints) {
    Point2<double> p{ 1.0, 2.0 };
    Segment2<double> seg(p, p);
    EXPECT_TRUE(seg.IsDegenerate());
}

TEST(Segment2Test, IsDegenerateLessThanEpsilon) {
    Point2<double> p1{ 1.0, 2.0 };
    Point2<double> p2{ 1.0 + EPSILON<double> * 0.5, 2.0 };
    Segment2<double> seg(p1, p2);
    EXPECT_TRUE(seg.IsDegenerate());
}

TEST(Segment2Test, IsDegenerateMoreThanEpsilon) {
    Point2<double> p1{ 1.0, 2.0 };
    Point2<double> p2{ 1.0 + EPSILON<double> * 1.5, 2.0 };
    Segment2<double> seg(p1, p2);
    EXPECT_FALSE(seg.IsDegenerate());
}

TEST(Segment2Test, IsDegenerateTooMoreThanEpsilon) {
    Point2<double> p1{ 1.0, 2.0 };
    Point2<double> p2{ 2.0, 2.0 };
    Segment2<double> seg(p1, p2);
    EXPECT_FALSE(seg.IsDegenerate());
}