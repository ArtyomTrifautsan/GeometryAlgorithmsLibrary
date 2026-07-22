#include "gtest/gtest.h"
#include <GeometryCore/Primitives/Vector3.h>

using namespace Geometry;

TEST(Vector3Test, DefaultConstructor) {
    Vector3<double> v;
    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
}

TEST(Vector3Test, ParametrizedConstructor) {
    Vector3<double> v(3.5, -2.0, 4.1);
    EXPECT_DOUBLE_EQ(v.x, 3.5);
    EXPECT_DOUBLE_EQ(v.y, -2.0);
    EXPECT_DOUBLE_EQ(v.z, 4.1);
}

TEST(Vector3Test, LengthCalculations) {
    Vector3<double> v(1.0, 2.0, 2.0);
    EXPECT_DOUBLE_EQ(v.SqrLen(), 9.0);
    EXPECT_DOUBLE_EQ(v.Len(), 3.0);
}

TEST(Vector3Test, NormalizeSuccess) {
    Vector3<double> v(0.0, 3.0, 4.0);
    v.Normalize();
    EXPECT_NEAR(v.x, 0.0, 1e-9);
    EXPECT_NEAR(v.y, 0.6, 1e-9);
    EXPECT_NEAR(v.z, 0.8, 1e-9);
    EXPECT_NEAR(v.Len(), 1.0, 1e-9);
}

TEST(Vector3Test, NormalizeZeroLength) {
    Vector3<double> v(0.0, 0.0, 0.0);
    v.Normalize();
    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
}

TEST(Vector3Test, UnaryMinus) {
    Vector3<double> v(1.0, -2.5, 3.0);
    Vector3<double> neg = -v;
    EXPECT_DOUBLE_EQ(neg.x, -1.0);
    EXPECT_DOUBLE_EQ(neg.y, 2.5);
    EXPECT_DOUBLE_EQ(neg.z, -3.0);
}

TEST(Vector3Test, MethodPlus) {
    Vector3<double> v1(1.0, 1.0, 1.0);
    Vector3<double> v2(2.0, 3.0, 4.0);
    v1 += v2;
    EXPECT_DOUBLE_EQ(v1.x, 3.0);
    EXPECT_DOUBLE_EQ(v1.y, 4.0);
    EXPECT_DOUBLE_EQ(v1.z, 5.0);
}

TEST(Vector3Test, MethodMinus) {
    Vector3<double> v1(1.0, 1.0, 1.0);
    Vector3<double> v2(2.0, 3.0, 4.0);
    v1 -= v2;
    EXPECT_DOUBLE_EQ(v1.x, -1.0);
    EXPECT_DOUBLE_EQ(v1.y, -2.0);
    EXPECT_DOUBLE_EQ(v1.z, -3.0);
}

TEST(Vector3Test, FuncPlus) {
    Vector3<double> v1(1.0, 1.0, 1.0);
    Vector3<double> v2(2.0, 3.0, 4.0);
    Vector3<double> sum = v1 + v2;
    EXPECT_DOUBLE_EQ(sum.x, 3.0);
    EXPECT_DOUBLE_EQ(sum.y, 4.0);
    EXPECT_DOUBLE_EQ(sum.z, 5.0);
}

TEST(Vector3Test, FuncMinus) {
    Vector3<double> v1(1.0, 1.0, 1.0);
    Vector3<double> v2(2.0, 3.0, 4.0);
    Vector3<double> sub = v1 - v2;
    EXPECT_DOUBLE_EQ(sub.x, -1.0);
    EXPECT_DOUBLE_EQ(sub.y, -2.0);
    EXPECT_DOUBLE_EQ(sub.z, -3.0);
}

TEST(Vector3Test, MethodProductByScalar) {
    Vector3<double> v(1.0, 1.0, 1.0);
    v *= 5.0;
    EXPECT_DOUBLE_EQ(v.x, 5.0);
    EXPECT_DOUBLE_EQ(v.y, 5.0);
    EXPECT_DOUBLE_EQ(v.z, 5.0);
}

TEST(Vector3Test, FuncsProductVector3ByScalar) {
    Vector3<double> v(1.0, 1.0, 1.0);
    Vector3<double> v2 = v * 5.0;
    EXPECT_DOUBLE_EQ(v2.x, 5.0);
    EXPECT_DOUBLE_EQ(v2.y, 5.0);
    EXPECT_DOUBLE_EQ(v2.z, 5.0);
}

TEST(Vector3Test, FuncsProductScalarByVector3) {
    Vector3<double> v(1.0, 1.0, 1.0);
    Vector3<double> v3 = 2.0 * v;
    EXPECT_DOUBLE_EQ(v3.x, 2.0);
    EXPECT_DOUBLE_EQ(v3.y, 2.0);
    EXPECT_DOUBLE_EQ(v3.z, 2.0);
}

TEST(Vector3Test, DotProduct) {
    Vector3<double> v1(1.0, 2.0, 3.0);
    Vector3<double> v2(2.0, 3.0, 4.0);
    double dot_result = Dot(v1, v2);
    EXPECT_DOUBLE_EQ(dot_result, 20.0);
}

TEST(Vector3Test, CrossProduct) {
    Vector3<double> v1(1.0, 2.0, 3.0);
    Vector3<double> v2(4.0, 5.0, 6.0);

    Vector3<double> cross_result = Cross(v1, v2);

    EXPECT_DOUBLE_EQ(cross_result.x, -3.0);
    EXPECT_DOUBLE_EQ(cross_result.y, 6.0);
    EXPECT_DOUBLE_EQ(cross_result.z, -3.0);
}

TEST(Vector3Test, AreEqual_CompileTime)
{
    constexpr Vector3<float> v1{ -1.0f, -2.0f, -3.0f };
    constexpr Vector3<float> v2{ -1.0f, -2.0f, -3.0f };
    static_assert(AreEqual(v1, v2), "Compile-time AreEqual failed for Vector3");
}

TEST(Vector3Test, AreEqual_ExactMatch)
{
    Vector3<double> v1{ 0.0, 1.0, 2.0 };
    Vector3<double> v2{ 0.0, 1.0, 2.0 };
    EXPECT_TRUE(AreEqual(v1, v2));
}

TEST(Vector3Test, AreEqual_WithinEpsilon)
{
    Vector3<double> v1{ 0.0, 1.0, 2.0 };
    Vector3<double> v2{ v1.x + (EPSILON<double> *0.5), v1.y, v1.z };
    EXPECT_TRUE(AreEqual(v1, v2));
}

TEST(Vector3Test, AreEqual_OutsideEpsilon)
{
    Vector3<double> v1{ 0.0, 1.0, 2.0 };
    Vector3<double> v2{ v1.x, v1.y, v1.z + (EPSILON<double> *1.5) };
    EXPECT_FALSE(AreEqual(v1, v2));
}

TEST(Vector3Test, Parallel_True)
{
    Vector3<double> v1(2.0, 4.0, 6.0);
    Vector3<double> v2(1.0, 2.0, 3.0);

    EXPECT_TRUE(Parallel(v1, v2));
}

TEST(Vector3Test, Parallel_True_OppositeDirection)
{
    Vector3<double> v1(1.0, 2.0, 3.0);
    Vector3<double> v2(-2.0, -4.0, -6.0);

    EXPECT_TRUE(Parallel(v1, v2));
}

TEST(Vector3Test, Parallel_False)
{
    Vector3<double> v1(2.0, 4.0, 6.0);
    Vector3<double> v2(1.0, 5.0, 2.0);

    EXPECT_FALSE(Parallel(v1, v2));
}

TEST(Vector3Test, Parallel_NegativeCrossProduct)
{
    Vector3<double> v1(1.0, 0.0, 0.0);
    Vector3<double> v2(0.0, -1.0, 0.0);

    EXPECT_FALSE(Parallel(v1, v2));
}

TEST(Vector3Test, Parallel_BothZero)
{
    Vector3<double> v1(0.0, 0.0, 0.0);
    Vector3<double> v2(0.0, 0.0, 0.0);

    EXPECT_FALSE(Parallel(v1, v2));
}

TEST(Vector3Test, Parallel_OneZero)
{
    Vector3<double> v1(0.0, 0.0, 0.0);
    Vector3<double> v2(1.0, 1.0, 1.0);

    EXPECT_FALSE(Parallel(v1, v2));
    EXPECT_FALSE(Parallel(v2, v1));
}

TEST(Vector3Test, Perpendicular_True)
{
    Vector3<double> v1(1.0, 2.0, 3.0);
    Vector3<double> v2(2.0, 2.0, -2.0);

    EXPECT_TRUE(Perpendicular(v1, v2));
}

TEST(Vector3Test, Perpendicular_False)
{
    Vector3<double> v1(1.0, 2.0, 3.0);
    Vector3<double> v2(1.0, 1.0, 1.0);

    EXPECT_FALSE(Perpendicular(v1, v2));
}

TEST(Vector3Test, Perpendicular_NegativeDotProduct)
{
    Vector3<double> v1(1.0, 0.0, 0.0);
    Vector3<double> v2(-1.0, 1.0, 0.0);

    EXPECT_FALSE(Perpendicular(v1, v2));
}

TEST(Vector3Test, Perpendicular_BothZero)
{
    Vector3<double> v1(0.0, 0.0, 0.0);
    Vector3<double> v2(0.0, 0.0, 0.0);

    EXPECT_FALSE(Perpendicular(v1, v2));
}

TEST(Vector3Test, Perpendicular_OneZero)
{
    Vector3<double> v1(0.0, 0.0, 0.0);
    Vector3<double> v2(1.0, 0.0, 0.0);

    EXPECT_FALSE(Perpendicular(v1, v2));
    EXPECT_FALSE(Perpendicular(v2, v1));
}

TEST(Vector3Test, Parallel_NearlyParallel)
{
    Vector3<double> v1(1.0, 2.0, 3.0);
    Vector3<double> v2(1.0 + 1e-15, 2.0 + 2e-15, 3.0 + 3e-15);

    EXPECT_TRUE(Parallel(v1, v2));
}

TEST(Vector3Test, Perpendicular_NearlyPerpendicular)
{
    Vector3<double> v1(1.0, 0.0, 0.0);
    Vector3<double> v2(0.0, 1.0, 1e-15);

    EXPECT_TRUE(Perpendicular(v1, v2));
}