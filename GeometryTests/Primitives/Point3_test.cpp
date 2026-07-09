#include "gtest/gtest.h"

#include <GeometryCore/Primitives/Point3.h>
#include <GeometryCore/Primitives/Vector3.h>
#include <GeometryCore/Math/Constants.h>

using namespace Geometry;

TEST(Point3Test, DefaultConstructor) {
    Point3<double> p;
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
    EXPECT_DOUBLE_EQ(p.z, 0.0);
}

TEST(Point3Test, ParametrizedConstructor) {
    Point3<double> p(1.5, -2.0, 10.3);
    EXPECT_DOUBLE_EQ(p.x, 1.5);
    EXPECT_DOUBLE_EQ(p.y, -2.0);
    EXPECT_DOUBLE_EQ(p.z, 10.3);
}

TEST(Point3Test, PointMinusPointEqualsVector) {
    const Point3<double> p1(10.0, 5.0, 3.0);
    const Point3<double> p2(3.0, 2.0, 3.0);

    Vector3<double> v = p1 - p2;

    EXPECT_DOUBLE_EQ(v.x, 7.0);
    EXPECT_DOUBLE_EQ(v.y, 3.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);

    EXPECT_DOUBLE_EQ(p1.z, 3.0);
    EXPECT_DOUBLE_EQ(p2.z, 3.0);
}

TEST(Point3Test, PointPlusVectorEqualsPoint) {
    const Point3<double> p(1.0, 2.0, -3.0);
    const Vector3<double> v(3.0, 4.0, 5.0);

    Point3<double> result = p + v;

    EXPECT_DOUBLE_EQ(result.x, 4.0);
    EXPECT_DOUBLE_EQ(result.y, 6.0);
    EXPECT_DOUBLE_EQ(result.z, 2.0);
}

TEST(Point3Test, PointMinusVectorEqualsPoint) {
    const Point3<double> p(5.0, 5.0, 5.0);
    const Vector3<double> v(1.5, 2.5, 3.5);

    Point3<double> result = p - v;

    EXPECT_DOUBLE_EQ(result.x, 3.5);
    EXPECT_DOUBLE_EQ(result.y, 2.5);
    EXPECT_DOUBLE_EQ(result.z, 1.5);
}

TEST(Point3Test, OperatorPlusAssign) {
    Point3<double> p(1.0, 2.0, 3.0);
    const Vector3<double> v(4.0, 5.0, 6.0);

    Point3<double>& ref = (p += v);

    EXPECT_DOUBLE_EQ(p.x, 5.0);
    EXPECT_DOUBLE_EQ(p.y, 7.0);
    EXPECT_DOUBLE_EQ(p.z, 9.0);
    EXPECT_EQ(&ref, &p);
}

TEST(Point3Test, OperatorMinusAssign) {
    Point3<double> p(10.0, 10.0, 10.0);
    const Vector3<double> v(1.5, 2.5, 3.5);

    Point3<double>& ref = (p -= v);

    EXPECT_DOUBLE_EQ(p.x, 8.5);
    EXPECT_DOUBLE_EQ(p.y, 7.5);
    EXPECT_DOUBLE_EQ(p.z, 6.5);
    EXPECT_EQ(&ref, &p);
}

TEST(Point3Test, AreEqual_CompileTime)
{
    constexpr Point3<float> p1{ 1.0f, 2.0f, 3.0f };
    constexpr Point3<float> p2{ 1.0f, 2.0f, 3.0f };
    static_assert(AreEqual(p1, p2), "Compile-time AreEqual failed for Point3");
}

TEST(Point3Test, AreEqual_ExactMatch)
{
    Point3<double> p1{ 1.0, 2.0, 3.0 };
    Point3<double> p2{ 1.0, 2.0, 3.0 };
    EXPECT_TRUE(AreEqual(p1, p2));
}

TEST(Point3Test, AreEqual_WithinEpsilon)
{
    Point3<double> p1{ 1.0, 2.0, 3.0 };
    Point3<double> p2{ 1.0, 2.0, 3.0 - (EPSILON<double> *0.5) };
    EXPECT_TRUE(AreEqual(p1, p2));
}

TEST(Point3Test, AreEqual_OutsideEpsilon)
{
    Point3<double> p1{ 1.0, 2.0, 3.0 };
    Point3<double> p2{ 1.0, 2.0, 3.0 - (EPSILON<double> *1.5) };
    EXPECT_FALSE(AreEqual(p1, p2));
}