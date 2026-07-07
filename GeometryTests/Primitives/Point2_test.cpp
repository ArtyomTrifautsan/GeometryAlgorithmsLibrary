#include "gtest/gtest.h"
#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/Primitives/Vector2.h>

using namespace Geometry;


TEST(Point2Test, DefaultConstructor) {
    Point2<double> p;
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
}

TEST(Point2Test, ParametrizedConstructor) {
    Point2<double> p(5.5, -3.14);
    EXPECT_DOUBLE_EQ(p.x, 5.5);
    EXPECT_DOUBLE_EQ(p.y, -3.14);
}

TEST(Point2Test, PointMinusPoint) {
    const Point2<double> p1(10.0, 5.0);
    const Point2<double> p2(3.0, 2.0);

    Vector2<double> v = p1 - p2;

    EXPECT_DOUBLE_EQ(v.x, 7.0);
    EXPECT_DOUBLE_EQ(v.y, 3.0);

    // Check that starting points have not changed
    EXPECT_DOUBLE_EQ(p1.x, 10.0);
    EXPECT_DOUBLE_EQ(p2.x, 3.0);
}

TEST(Point2Test, PointPlusVector) {
    const Point2<double> p(1.0, 2.0);
    const Vector2<double> v(3.0, 4.0);

    Point2<double> result = p + v;

    EXPECT_DOUBLE_EQ(result.x, 4.0);
    EXPECT_DOUBLE_EQ(result.y, 6.0);
}

TEST(Point2Test, PointMinusVector) {
    const Point2<double> p(5.0, 5.0);
    const Vector2<double> v(1.5, 2.5);

    Point2<double> result = p - v;

    EXPECT_DOUBLE_EQ(result.x, 3.5);
    EXPECT_DOUBLE_EQ(result.y, 2.5);
}

TEST(Point2Test, OperatorPlusAssign) {
    Point2<double> p(1.0, 2.0);
    const Vector2<double> v(3.0, 4.0);

    Point2<double>& ref = (p += v);

    EXPECT_DOUBLE_EQ(p.x, 4.0);
    EXPECT_DOUBLE_EQ(p.y, 6.0);
    EXPECT_EQ(&ref, &p);
}

TEST(Point2Test, OperatorMinusAssign) {
    Point2<double> p(5.0, 5.0);
    const Vector2<double> v(1.5, 2.5);

    Point2<double>& ref = (p -= v);

    EXPECT_DOUBLE_EQ(p.x, 3.5);
    EXPECT_DOUBLE_EQ(p.y, 2.5);
    EXPECT_EQ(&ref, &p);
}