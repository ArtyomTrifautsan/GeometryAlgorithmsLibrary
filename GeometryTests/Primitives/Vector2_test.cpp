#include "gtest/gtest.h"
#include <GeometryCore/Primitives/Vector2.h>

using namespace Geometry;

TEST(Vector2Test, DefaultConstructor) {
    Vector2<double> v;
    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
}

TEST(Vector2Test, ParametrizedConstructor) {
    Vector2<double> v(3.5, -2.0);
    EXPECT_DOUBLE_EQ(v.x, 3.5);
    EXPECT_DOUBLE_EQ(v.y, -2.0);
}

TEST(Vector2Test, LengthCalculations) {
    Vector2<double> v(3.0, 4.0);
    EXPECT_DOUBLE_EQ(v.SqrLen(), 25.0);
    EXPECT_DOUBLE_EQ(v.Len(), 5.0);
}

TEST(Vector2Test, NormalizeSuccess) {
    Vector2<double> v(3.0, 0.0);
    v.Normalize();
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.Len(), 1.0);
}

TEST(Vector2Test, NormalizeThrowsOnZeroLength) {
    Vector2<double> v(0.0, 0.0);
    EXPECT_THROW(v.Normalize(), std::runtime_error);
}

TEST(Vector2Test, UnaryMinus) {
    Vector2<double> v(1.0, -2.5);
    Vector2<double> neg = -v;
    EXPECT_DOUBLE_EQ(neg.x, -1.0);
    EXPECT_DOUBLE_EQ(neg.y, 2.5);
}

TEST(Vector2Test, MethodPlus) {
    Vector2<double> v1(1.0, 1.0);
    Vector2<double> v2(2.0, 3.0);
    v1 += v2;
    EXPECT_DOUBLE_EQ(v1.x, 3.0);
    EXPECT_DOUBLE_EQ(v1.y, 4.0);
}

TEST(Vector2Test, MethodMinus) {
    Vector2<double> v1(1.0, 1.0);
    Vector2<double> v2(2.0, 3.0);
    v1 -= v2;
    EXPECT_DOUBLE_EQ(v1.x, -1.0);
    EXPECT_DOUBLE_EQ(v1.y, -2.0);
}

TEST(Vector2Test, FuncPlus) {
    Vector2<double> v1(1.0, 1.0);
    Vector2<double> v2(2.0, 3.0);
    Vector2<double> sum = v1 + v2;
    EXPECT_DOUBLE_EQ(sum.x, 3.0);
    EXPECT_DOUBLE_EQ(sum.y, 4.0);
}

TEST(Vector2Test, FuncMinus) {
    Vector2<double> v1(1.0, 1.0);
    Vector2<double> v2(2.0, 3.0);
    Vector2<double> sub = v1 - v2;
    EXPECT_DOUBLE_EQ(sub.x, -1.0);
    EXPECT_DOUBLE_EQ(sub.y, -2.0);
}

TEST(Vector2Test, MethodProductByScalar) {
    Vector2<double> v(1.0, 1.0);
    v *= 5.0;
    EXPECT_DOUBLE_EQ(v.x, 5.0);
    EXPECT_DOUBLE_EQ(v.y, 5.0);
}

TEST(Vector2Test, FuncsProductVector2ByScalar) {
    Vector2<double> v(1.0, 1.0);

    Vector2<double> v2 = v * 5.0;
    EXPECT_DOUBLE_EQ(v2.x, 5.0);
    EXPECT_DOUBLE_EQ(v2.y, 5.0);
}

TEST(Vector2Test, FuncsProductScalarByVector2) {
    Vector2<double> v(1.0, 1.0);

    Vector2<double> v3 = 2.0 * v;
    EXPECT_DOUBLE_EQ(v3.x, 2.0);
    EXPECT_DOUBLE_EQ(v3.y, 2.0);
}

TEST(Vector2Test, DotProduct)
{
    Vector2<double> v1(1.0, 2.0);
    Vector2<double> v2(2.0, 3.0);
    double dot_result = Dot(v1, v2);
    EXPECT_DOUBLE_EQ(dot_result, 8.0);
}

TEST(Vector2Test, CrossProduct)
{
    Vector2<double> v1(1.0, 2.0);
    Vector2<double> v2(2.0, 3.0);
    double cross_result = Cross(v1, v2);
    EXPECT_DOUBLE_EQ(cross_result, -1.0);
}