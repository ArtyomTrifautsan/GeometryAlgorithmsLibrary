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