#include "gtest/gtest.h"
#include <GeometryCore/Primitives/Segment3.h>
#include <GeometryCore/Primitives/Point3.h>
#include <GeometryCore/Primitives/Vector3.h>

using namespace Geometry;


TEST(Segment3Test, DefaultConstructor) {
    Segment3<double> seg;
    EXPECT_DOUBLE_EQ(seg.start.x, 0.0);
    EXPECT_DOUBLE_EQ(seg.start.y, 0.0);
    EXPECT_DOUBLE_EQ(seg.start.z, 0.0);
    EXPECT_DOUBLE_EQ(seg.end.x, 0.0);
    EXPECT_DOUBLE_EQ(seg.end.y, 0.0);
    EXPECT_DOUBLE_EQ(seg.end.z, 0.0);
}

TEST(Segment3Test, ParamentrizedConstructor) {
    Segment3<double> seg{ Point3<double>{1.0, -1.0, 2.0}, Point3<double>{3.0, 4.0, 5.0} };
    EXPECT_DOUBLE_EQ(seg.start.x, 1.0);
    EXPECT_DOUBLE_EQ(seg.start.y, -1.0);
    EXPECT_DOUBLE_EQ(seg.start.z, 2.0);
    EXPECT_DOUBLE_EQ(seg.end.x, 3.0);
    EXPECT_DOUBLE_EQ(seg.end.y, 4.0);
    EXPECT_DOUBLE_EQ(seg.end.z, 5.0);
}

TEST(Segment3Test, VectorMethod) {
    Segment3<double> seg(Point3<double>(1.0, 1.0, 1.0), Point3<double>(3.0, 4.0, 1.0));
    auto v = seg.Vector();
    EXPECT_DOUBLE_EQ(v.x, 2.0);
    EXPECT_DOUBLE_EQ(v.y, 3.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
}

TEST(Segment3Test, SqrLength) {
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 3.0, 6.0));
    EXPECT_DOUBLE_EQ(seg.SqrLength(), 49.0);
}

TEST(Segment3Test, Length) {
    Segment3<double> seg(Point3<double>(0.0, 0.0, 0.0), Point3<double>(2.0, 3.0, 6.0));
    EXPECT_DOUBLE_EQ(seg.Length(), 7.0);
}

TEST(Segment3Test, MidpointCalculation) {
    Segment3<double> seg(Point3<double>(10.0, -4.0, 2.0), Point3<double>(0.0, 4.0, 6.0));
    auto mid = seg.Midpoint();

    EXPECT_DOUBLE_EQ(mid.x, 5.0);
    EXPECT_DOUBLE_EQ(mid.y, 0.0);
    EXPECT_DOUBLE_EQ(mid.z, 4.0);
}

TEST(Segment3Test, PointAtCalculation) {
    Segment3<double> seg(Point3<double>(1.0, 2.0, 3.0), Point3<double>(5.0, 10.0, 15.0));
    auto point_at_ = seg.PointAt(0.25);

    EXPECT_DOUBLE_EQ(point_at_.x, 2.0);
    EXPECT_DOUBLE_EQ(point_at_.y, 4.0);
    EXPECT_DOUBLE_EQ(point_at_.z, 6.0);
}

TEST(Segment3Test, IsDegenerateSamePoints) {
    Point3<double> p{ 1.0, 2.0, 3.0 };
    Segment3<double> seg(p, p);
    EXPECT_TRUE(seg.IsDegenerate());
}

TEST(Segment3Test, IsDegenerateLessThanEpsilon) {
    Point3<double> p1{ 1.0, 2.0, 3.0 };
    Point3<double> p2{ 1.0 + EPSILON<double> *0.5, 2.0, 3.0 };
    Segment3<double> seg(p1, p2);
    EXPECT_TRUE(seg.IsDegenerate());
}

TEST(Segment3Test, IsDegenerateMoreThanEpsilon) {
    Point3<double> p1{ 1.0, 2.0, 3.0 };
    Point3<double> p2{ 1.0 + EPSILON<double> *1.5, 2.0, 3.0 };
    Segment3<double> seg(p1, p2);
    EXPECT_FALSE(seg.IsDegenerate());
}

TEST(Segment3Test, IsDegenerateTooMoreThanEpsilon) {
    Point3<double> p1{ 1.0, 2.0, 3.0 };
    Point3<double> p2{ 2.0, 2.0, 3.0 };
    Segment3<double> seg(p1, p2);
    EXPECT_FALSE(seg.IsDegenerate());
}