#include <gtest/gtest.h>

#include <GeometryCore/Math/Utils.h>
#include <GeometryCore/Math/Constants.h>

using namespace Geometry;


// === Double ===

TEST(MathUtilsTest_Double, IsZero) 
{
    EXPECT_TRUE(IsZero<double>(0.0));

    // Within the error margin (half an epsilon)
    EXPECT_TRUE(IsZero<double>(EPSILON<double> * 0.5));
    EXPECT_TRUE(IsZero<double>(-EPSILON<double> * 0.5));

    // Beyond the margin of error (one and a half epsilons)
    EXPECT_FALSE(IsZero<double>(EPSILON<double> * 1.5));
    EXPECT_FALSE(IsZero<double>(-EPSILON<double> * 1.5));
}

TEST(MathUtilsTest_Double, IsZeroWithEPS)
{
    EXPECT_TRUE(IsZero<double>(0.0, EPSILON<double>));

    // Within the error margin (half an epsilon)
    EXPECT_TRUE(IsZero<double>(EPSILON<double> *0.05, EPSILON<double> *0.1));
    EXPECT_TRUE(IsZero<double>(-EPSILON<double> *0.05, EPSILON<double> * 0.1));

    // Beyond the margin of error (one and a half epsilons)
    EXPECT_FALSE(IsZero<double>(EPSILON<double>, EPSILON<double> *0.1));
    EXPECT_FALSE(IsZero<double>(-EPSILON<double>, EPSILON<double> *0.1));
}

TEST(MathUtilsTest_Double, AreEqual) 
{
    const double base = 5.0;
    EXPECT_TRUE(AreEqual<double>(base, base));

    // The difference within Epsilon
    EXPECT_TRUE(AreEqual<double>(base + EPSILON<double> *0.5, base));
    EXPECT_TRUE(AreEqual<double>(base - EPSILON<double> *0.5, base));

    // The difference beyond Epsilon
    EXPECT_FALSE(AreEqual<double>(base + EPSILON<double> *1.5, base));
    EXPECT_FALSE(AreEqual<double>(base - EPSILON<double> *1.5, base));
}

TEST(MathUtilsTest_Double, IsGreaterOrEqual)
{
    const double base = 5.0;
    EXPECT_TRUE(IsGreaterOrEqual<double>(base + 1.0, base));
    EXPECT_TRUE(IsGreaterOrEqual<double>(base, base));

    // A little less, but within the epsilon range
    EXPECT_TRUE(IsGreaterOrEqual<double>(base - EPSILON<double> * 0.5, base));

    // Clearly less (went beyond epsilon)
    EXPECT_FALSE(IsGreaterOrEqual<double>(base - EPSILON<double> * 1.5, base));
}

TEST(MathUtilsTest_Double, IsLessOrEqual)
{
    const double base = 5.0;
    EXPECT_TRUE(IsLessOrEqual<double>(base - 1.0, base));
    EXPECT_TRUE(IsLessOrEqual<double>(base, base));

    // A little more, but within the epsilon range
    EXPECT_TRUE(IsLessOrEqual<double>(base + EPSILON<double> *0.5, base));

    // Clearly more (went beyond epsilon)
    EXPECT_FALSE(IsLessOrEqual<double>(base + EPSILON<double> *1.5, base));
}

TEST(MathUtilsTest_Double, IsGreaterOrEqualWithTolerance)
{
    const double base = 5.0;
    const double tol = 0.1;

    EXPECT_TRUE(IsGreaterOrEqual<double>(base + 1.0, base, tol));
    EXPECT_TRUE(IsGreaterOrEqual<double>(base, base, tol));

    EXPECT_TRUE(IsGreaterOrEqual<double>(base - tol * 0.5, base, tol));
    EXPECT_FALSE(IsGreaterOrEqual<double>(base - tol * 1.5, base, tol));
}

TEST(MathUtilsTest_Double, IsLessOrEqualWithTolerance)
{
    const double base = 5.0;
    const double tol = 0.1;

    EXPECT_TRUE(IsLessOrEqual<double>(base - 1.0, base, tol));
    EXPECT_TRUE(IsLessOrEqual<double>(base, base, tol));

    EXPECT_TRUE(IsLessOrEqual<double>(base + tol * 0.5, base, tol));
    EXPECT_FALSE(IsLessOrEqual<double>(base + tol * 1.5, base, tol));
}


// === Float ===


TEST(MathUtilsTest_Float, IsZero)
{
    EXPECT_TRUE(IsZero<float>(0.0f));

    // Within the error margin (half an epsilon)
    EXPECT_TRUE(IsZero<float>(EPSILON<float> *0.5f));
    EXPECT_TRUE(IsZero<float>(-EPSILON<float> *0.5f));

    // Beyond the margin of error (one and a half epsilons)
    EXPECT_FALSE(IsZero<float>(EPSILON<float> *1.5f));
    EXPECT_FALSE(IsZero<float>(-EPSILON<float> *1.5f));
}

TEST(MathUtilsTest_Float, IsZeroWithEPS)
{
    EXPECT_TRUE(IsZero<float>(0.0f, EPSILON<float>));

    // Within the error margin (half an epsilon)
    EXPECT_TRUE(IsZero<float>(EPSILON<float> *0.05f, EPSILON<float> *0.1f));
    EXPECT_TRUE(IsZero<float>(-EPSILON<float> *0.05f, EPSILON<float> *0.1f));

    // Beyond the margin of error (one and a half epsilons)
    EXPECT_FALSE(IsZero<float>(EPSILON<float>, EPSILON<float> *0.1f));
    EXPECT_FALSE(IsZero<float>(-EPSILON<float>, EPSILON<float> *0.1f));
}


TEST(MathUtilsTest_Float, AreEqual)
{
    const float base = 5.0f;
    EXPECT_TRUE(AreEqual<float>(base, base));

    // The difference within Epsilon
    EXPECT_TRUE(AreEqual<float>(base + EPSILON<float> *0.5f, base));
    EXPECT_TRUE(AreEqual<float>(base - EPSILON<float> *0.5f, base));

    // The difference beyond Epsilon
    EXPECT_FALSE(AreEqual<float>(base + EPSILON<float> *1.5f, base));
    EXPECT_FALSE(AreEqual<float>(base - EPSILON<float> *1.5f, base));
}

TEST(MathUtilsTest_Float, IsGreaterOrEqual)
{
    const float base = 5.0f;
    EXPECT_TRUE(IsGreaterOrEqual<float>(base + 1.0f, base));
    EXPECT_TRUE(IsGreaterOrEqual<float>(base, base));

    // A little less, but within the epsilon range
    EXPECT_TRUE(IsGreaterOrEqual<float>(base - EPSILON<float> *0.5f, base));

    // Clearly less (went beyond epsilon)
    EXPECT_FALSE(IsGreaterOrEqual<float>(base - EPSILON<float> *1.5f, base));
}

TEST(MathUtilsTest_Float, IsLessOrEqual) {
    const float base = 5.0f;
    EXPECT_TRUE(IsLessOrEqual<float>(base - 1.0f, base));
    EXPECT_TRUE(IsLessOrEqual<float>(base, base));

    // A little more, but within the epsilon range
    EXPECT_TRUE(IsLessOrEqual<float>(base + EPSILON<float> *0.5f, base));

    // Clearly more (went beyond epsilon)
    EXPECT_FALSE(IsLessOrEqual<float>(base + EPSILON<float> *1.5f, base));
}

TEST(MathUtilsTest_Float, IsGreaterOrEqualWithTolerance)
{
    const float base = 5.0f;
    const float tol = 0.1f;

    EXPECT_TRUE(IsGreaterOrEqual<float>(base + 1.0f, base, tol));
    EXPECT_TRUE(IsGreaterOrEqual<float>(base, base, tol));

    EXPECT_TRUE(IsGreaterOrEqual<float>(base - tol * 0.5f, base, tol));
    EXPECT_FALSE(IsGreaterOrEqual<float>(base - tol * 1.5f, base, tol));
}

TEST(MathUtilsTest_Float, IsLessOrEqualWithTolerance)
{
    const float base = 5.0f;
    const float tol = 0.1f;

    EXPECT_TRUE(IsLessOrEqual<float>(base - 1.0f, base, tol));
    EXPECT_TRUE(IsLessOrEqual<float>(base, base, tol));

    EXPECT_TRUE(IsLessOrEqual<float>(base + tol * 0.5f, base, tol));
    EXPECT_FALSE(IsLessOrEqual<float>(base + tol * 1.5f, base, tol));
}