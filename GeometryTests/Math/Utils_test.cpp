#include <gtest/gtest.h>

#include <GeometryCore/Math/Utils.h>
#include "GeometryCore/Math/Tolerance.h"
#include <GeometryCore/Math/Constants.h>

using namespace Geometry;


// === OLD TESTS ===

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
    EXPECT_FALSE(AreEqual<double>(base + EPSILON<double> * 1.5, base));
    EXPECT_FALSE(AreEqual<double>(base - EPSILON<double> * 1.5, base));
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









// === IsNumericallyZero double ===

TEST(MathUtils_Double, IsNumericallyZero_NonZero)
{
    EXPECT_FALSE(IsNumericallyZero<double>(3.0));
}

TEST(MathUtils_Double, IsNumericallyZero_NegativeNonZero)
{
    EXPECT_FALSE(IsNumericallyZero<double>(-3.0));
}

TEST(MathUtils_Double, IsNumericallyZero_Zero)
{
    EXPECT_TRUE(IsNumericallyZero<double>(0.0));
}

TEST(MathUtils_Double, IsNumericallyZero_NegativeZero)
{
    EXPECT_TRUE(IsNumericallyZero<double>(-0.0));
}

TEST(MathUtils_Double, IsNumericallyZero_SlightlyMoreThanMathEpsilon)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    EXPECT_FALSE(IsNumericallyZero<double>(mathEps * 2.0));
}

TEST(MathUtils_Double, IsNumericallyZero_NegativeSlightlyMoreThanMathEpsilon)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    EXPECT_FALSE(IsNumericallyZero<double>(-mathEps * 2.0));
}

TEST(MathUtils_Double, IsNumericallyZero_SlightlyLessThanMathEpsilon)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    EXPECT_TRUE(IsNumericallyZero<double>(mathEps * 0.4));
}

TEST(MathUtils_Double, IsNumericallyZero_NegativeSlightlyLessThanMathEpsilon)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    EXPECT_TRUE(IsNumericallyZero<double>(-mathEps * 0.4));
}

TEST(MathUtils_Double, IsNumericallyZero_HugeValue)
{
    EXPECT_FALSE(IsNumericallyZero<double>(1e12));
}

TEST(MathUtils_Double, IsNumericallyZero_ValueSmallerThanCustomTolerance)
{
    Tolerance<double> customTol;
    customTol.mathEpsilon = 10.0;
    EXPECT_TRUE(IsNumericallyZero<double>(5.0, customTol));
}

TEST(MathUtils_Double, IsNumericallyZero_ValueBiggerThanCustomTolerance)
{
    Tolerance<double> customTol;
    customTol.mathEpsilon = 10.0;
    EXPECT_FALSE(IsNumericallyZero<double>(15.0, customTol));
}


// === AreNumericallyEqual double ===

TEST(MathUtils_Double, AreNumericallyEqual_NotEqual)
{
    EXPECT_FALSE(AreNumericallyEqual<double>(5.0, 8.0));
}

TEST(MathUtils_Double, AreNumericallyEqual_DifferentSigns)
{
    EXPECT_FALSE(AreNumericallyEqual<double>(5.0, -5.0));
}

TEST(MathUtils_Double, AreNumericallyEqual_ExactEquality)
{
    EXPECT_TRUE(AreNumericallyEqual<double>(5.0, 5.0));
}

TEST(MathUtils_Double, AreNumericallyEqual_ZeroAndNegativeZero)
{
    EXPECT_TRUE(AreNumericallyEqual<double>(0.0, -0.0));
}

TEST(MathUtils_Double, AreNumericallyEqual_DifferenceSlightlyLessThanMathEpsilon)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    EXPECT_TRUE(AreNumericallyEqual<double>(1.0, 1.0 + mathEps * 0.4));
}

TEST(MathUtils_Double, AreNumericallyEqual_NegativeDifferenceSlightlyLessThanMathEpsilon)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    EXPECT_TRUE(AreNumericallyEqual<double>(-1.0, -1.0 - mathEps * 0.4));
}

TEST(MathUtils_Double, AreNumericallyEqual_DifferenceSlightlyMoreThanMathEpsilon)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    EXPECT_FALSE(AreNumericallyEqual<double>(1.0, 1.0 + mathEps * 2));
}

TEST(MathUtils_Double, AreNumericallyEqual_NegativeDifferenceSlightlyMoreThanMathEpsilon)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    EXPECT_FALSE(AreNumericallyEqual<double>(-1.0, -1.0 - mathEps * 2));
}

TEST(MathUtils_Double, AreNumericallyEqual_RelativeTolerance_LargeValues)
{
    // diff more than mathEpsilon, but less than mathEpsilon * max(Abs(a), Abs(b))
    const double eps = DefaultTolerance<double>.mathEpsilon;
    double a = 1e6;
    double b = 1e6 + eps * 1e5;
    EXPECT_TRUE(AreNumericallyEqual<double>(a, b));
}

TEST(MathUtils_Double, AreNumericallyEqual_HugeValues_ScaledDifferenceAllowed)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    const double hugeValue = 1e9;
    const double allowedDiff = hugeValue * mathEps;
    EXPECT_TRUE(AreNumericallyEqual<double>(hugeValue, hugeValue + allowedDiff * 0.4));
}

TEST(MathUtils_Double, AreNumericallyEqual_HugeValues_ScaledDifferenceRejected)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    const double hugeValue = 1e9;
    const double allowedDiff = hugeValue * mathEps;
    EXPECT_FALSE(AreNumericallyEqual<double>(hugeValue, hugeValue + allowedDiff * 2.0));
}

TEST(MathUtils_Double, AreNumericallyEqual_CustomTolerance)
{
    Tolerance<double> customTol;
    customTol.mathEpsilon = 0.5;
    EXPECT_TRUE(AreNumericallyEqual<double>(10.0, 14.0, customTol));
    EXPECT_FALSE(AreNumericallyEqual<double>(10.0, 30.0, customTol));
}

// === IsNumericallyGreaterOrEqual double ===

TEST(MathUtils_Double, IsNumericallyGreaterOrEqual_StrictlyGreater)
{
    EXPECT_TRUE(IsNumericallyGreaterOrEqual<double>(10.0, 5.0));
}

TEST(MathUtils_Double, IsNumericallyGreaterOrEqual_StrictlyLess)
{
    EXPECT_FALSE(IsNumericallyGreaterOrEqual<double>(5.0, 10.0));
}

TEST(MathUtils_Double, IsNumericallyGreaterOrEqual_SlightlyLess_WithinMathEpsilon)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    const double base = 1.0;
    EXPECT_TRUE(IsNumericallyGreaterOrEqual<double>(base, base + mathEps * 0.5));
}

TEST(MathUtils_Double, IsNumericallyGreaterOrEqual_SlightlyLess_OutsideMathEpsilon)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    const double base = 1.0;
    EXPECT_FALSE(IsNumericallyGreaterOrEqual<double>(base, base + mathEps * 2.0));
}

TEST(MathUtils_Double, IsNumericallyGreaterOrEqual_HugeValues_WithinScaledTolerance)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    const double hugeValue = 1e9;
    const double allowedDiff = hugeValue * mathEps;
    EXPECT_TRUE(IsNumericallyGreaterOrEqual<double>(hugeValue, hugeValue + allowedDiff * 0.5));
}

// === IsNumericallyLessOrEqual double ===

TEST(MathUtils_Double, IsNumericallyLessOrEqual_StrictlyLess)
{
    EXPECT_TRUE(IsNumericallyLessOrEqual<double>(5.0, 10.0));
}

TEST(MathUtils_Double, IsNumericallyLessOrEqual_StrictlyGreater)
{
    EXPECT_FALSE(IsNumericallyLessOrEqual<double>(10.0, 5.0));
}

TEST(MathUtils_Double, IsNumericallyLessOrEqual_SlightlyGreater_WithinMathEpsilon)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    const double base = 1.0;
    EXPECT_TRUE(IsNumericallyLessOrEqual<double>(base, base - mathEps * 0.5));
}

TEST(MathUtils_Double, IsNumericallyLessOrEqual_SlightlyGreater_OutsideMathEpsilon)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    const double base = 1.0;
    EXPECT_FALSE(IsNumericallyLessOrEqual<double>(base, base - mathEps * 2.0));
}

TEST(MathUtils_Double, IsNumericallyLessOrEqual_HugeValues_WithinScaledTolerance)
{
    const double mathEps = DefaultTolerance<double>.mathEpsilon;
    const double hugeValue = 1e9;
    const double allowedDiff = hugeValue * mathEps;
    EXPECT_TRUE(IsNumericallyLessOrEqual<double>(hugeValue, hugeValue - allowedDiff * 0.5));
}

// === IsGeometricallyZero double ===

TEST(MathUtils_Double, IsGeometricallyZero_NonZero)
{
    EXPECT_FALSE(IsGeometricallyZero<double>(3.0));
}

TEST(MathUtils_Double, IsGeometricallyZero_Zero)
{
    EXPECT_TRUE(IsGeometricallyZero<double>(0.0));
}

TEST(MathUtils_Double, IsGeometricallyZero_SlightlyLessThanConfusion)
{
    const double conf = DefaultTolerance<double>.geometricTolerance;
    EXPECT_TRUE(IsGeometricallyZero<double>(conf * 0.5));
}

TEST(MathUtils_Double, IsGeometricallyZero_NegativeSlightlyLessThanConfusion)
{
    const double conf = DefaultTolerance<double>.geometricTolerance;
    EXPECT_TRUE(IsGeometricallyZero<double>(-conf * 0.5));
}

TEST(MathUtils_Double, IsGeometricallyZero_SlightlyMoreThanConfusion)
{
    const double conf = DefaultTolerance<double>.geometricTolerance;
    EXPECT_FALSE(IsGeometricallyZero<double>(conf * 2.0));
}

TEST(MathUtils_Double, IsGeometricallyZero_NegativeSlightlyMoreThanConfusion)
{
    const double conf = DefaultTolerance<double>.geometricTolerance;
    EXPECT_FALSE(IsGeometricallyZero<double>(-conf * 2.0));
}

TEST(MathUtils_Double, IsGeometricallyZero_CustomTolerance)
{
    Tolerance<double> customTol;
    customTol.geometricTolerance = 0.5;
    EXPECT_TRUE(IsGeometricallyZero<double>(0.4, customTol));
    EXPECT_FALSE(IsGeometricallyZero<double>(0.6, customTol));
}

// === AreGeometricallyEqual double ===

TEST(MathUtils_Double, AreGeometricallyEqual_ExactEquality)
{
    EXPECT_TRUE(AreGeometricallyEqual<double>(5.0, 5.0));
}

TEST(MathUtils_Double, AreGeometricallyEqual_DifferenceSlightlyLessThanConfusion)
{
    const double conf = DefaultTolerance<double>.geometricTolerance;
    EXPECT_TRUE(AreGeometricallyEqual<double>(1.0, 1.0 + conf * 0.5));
}

TEST(MathUtils_Double, AreGeometricallyEqual_DifferenceSlightlyMoreThanConfusion)
{
    const double conf = DefaultTolerance<double>.geometricTolerance;
    EXPECT_FALSE(AreGeometricallyEqual<double>(1.0, 1.0 + conf * 2.0));
}

TEST(MathUtils_Double, AreGeometricallyEqual_HugeValues_AbsoluteToleranceEnforced)
{
    const double conf = DefaultTolerance<double>.geometricTolerance;
    const double hugeValue = 10000.0;
    EXPECT_TRUE(AreGeometricallyEqual<double>(hugeValue, hugeValue + conf * 0.5));
}

TEST(MathUtils_Double, AreGeometricallyEqual_HugeValues_OutsideAbsoluteTolerance)
{
    const double conf = DefaultTolerance<double>.geometricTolerance;
    const double hugeValue = 10000.0;
    EXPECT_FALSE(AreGeometricallyEqual<double>(hugeValue, hugeValue + conf * 2.0));
}

// === IsGeometricallyGreaterOrEqual double ===

TEST(MathUtils_Double, IsGeometricallyGreaterOrEqual_StrictlyGreater)
{
    EXPECT_TRUE(IsGeometricallyGreaterOrEqual<double>(10.0, 5.0));
}

TEST(MathUtils_Double, IsGeometricallyGreaterOrEqual_SlightlyLess_WithinConfusion)
{
    const double conf = DefaultTolerance<double>.geometricTolerance;
    EXPECT_TRUE(IsGeometricallyGreaterOrEqual<double>(5.0, 5.0 + conf * 0.5));
}

TEST(MathUtils_Double, IsGeometricallyGreaterOrEqual_SlightlyLess_OutsideConfusion)
{
    const double conf = DefaultTolerance<double>.geometricTolerance;
    EXPECT_FALSE(IsGeometricallyGreaterOrEqual<double>(5.0, 5.0 + conf * 2.0));
}

// === IsGeometricallyLessOrEqual double ===

TEST(MathUtils_Double, IsGeometricallyLessOrEqual_StrictlyLess)
{
    EXPECT_TRUE(IsGeometricallyLessOrEqual<double>(5.0, 10.0));
}

TEST(MathUtils_Double, IsGeometricallyLessOrEqual_SlightlyGreater_WithinConfusion)
{
    const double conf = DefaultTolerance<double>.geometricTolerance;
    EXPECT_TRUE(IsGeometricallyLessOrEqual<double>(5.0, 5.0 - conf * 0.5));
}

TEST(MathUtils_Double, IsGeometricallyLessOrEqual_SlightlyGreater_OutsideConfusion)
{
    const double conf = DefaultTolerance<double>.geometricTolerance;
    EXPECT_FALSE(IsGeometricallyLessOrEqual<double>(5.0, 5.0 - conf * 2.0));
}


// === IsNumericallyZero float ===

TEST(MathUtils_Float, IsNumericallyZero_NonZero)
{
    EXPECT_FALSE(IsNumericallyZero<float>(3.0f));
    EXPECT_FALSE(IsNumericallyZero<float>(-3.0f));
}

TEST(MathUtils_Float, IsNumericallyZero_Zero)
{
    EXPECT_TRUE(IsNumericallyZero<float>(0.0f));
    EXPECT_TRUE(IsNumericallyZero<float>(-0.0f));
}

TEST(MathUtils_Float, IsNumericallyZero_SlightlyLessThanMathEpsilon)
{
    const float mathEps = DefaultTolerance<float>.mathEpsilon;
    EXPECT_TRUE(IsNumericallyZero<float>(mathEps * 0.5f));
    EXPECT_TRUE(IsNumericallyZero<float>(-mathEps * 0.5f));
}

TEST(MathUtils_Float, IsNumericallyZero_SlightlyMoreThanMathEpsilon)
{
    const float mathEps = DefaultTolerance<float>.mathEpsilon;
    EXPECT_FALSE(IsNumericallyZero<float>(mathEps * 2.0f));
    EXPECT_FALSE(IsNumericallyZero<float>(-mathEps * 2.0f));
}

TEST(MathUtils_Float, IsNumericallyZero_CustomTolerance)
{
    Tolerance<float> customTol;
    customTol.mathEpsilon = 10.0f;
    EXPECT_TRUE(IsNumericallyZero<float>(5.0f, customTol));
    EXPECT_FALSE(IsNumericallyZero<float>(15.0f, customTol));
}

// === AreNumericallyEqual float ===

TEST(MathUtils_Float, AreNumericallyEqual_ExactEquality)
{
    EXPECT_TRUE(AreNumericallyEqual<float>(5.0f, 5.0f));
}

TEST(MathUtils_Float, AreNumericallyEqual_DifferenceSlightlyLessThanMathEpsilon)
{
    const float mathEps = DefaultTolerance<float>.mathEpsilon;
    EXPECT_TRUE(AreNumericallyEqual<float>(1.0f, 1.0f + mathEps * 0.5f));
}

TEST(MathUtils_Float, AreNumericallyEqual_DifferenceSlightlyMoreThanMathEpsilon)
{
    const float mathEps = DefaultTolerance<float>.mathEpsilon;
    EXPECT_FALSE(AreNumericallyEqual<float>(1.0f, 1.0f + mathEps * 2.0f));
}

TEST(MathUtils_Float, AreNumericallyEqual_HugeValues_ScaledDifferenceAllowed)
{
    const float mathEps = DefaultTolerance<float>.mathEpsilon;
    const float hugeValue = 1e5f;
    const float allowedDiff = hugeValue * mathEps;
    EXPECT_TRUE(AreNumericallyEqual<float>(hugeValue, hugeValue + allowedDiff * 0.5f));
    EXPECT_FALSE(AreNumericallyEqual<float>(hugeValue, hugeValue + allowedDiff * 2.0f));
}

// === IsNumericallyGreaterOrEqual float ===

TEST(MathUtils_Float, IsNumericallyGreaterOrEqual_SlightlyLess_WithinMathEpsilon)
{
    const float mathEps = DefaultTolerance<float>.mathEpsilon;
    const float base = 1.0f;
    EXPECT_TRUE(IsNumericallyGreaterOrEqual<float>(base, base + mathEps * 0.5f));
}

TEST(MathUtils_Float, IsNumericallyGreaterOrEqual_SlightlyLess_OutsideMathEpsilon)
{
    const float mathEps = DefaultTolerance<float>.mathEpsilon;
    const float base = 1.0f;
    EXPECT_FALSE(IsNumericallyGreaterOrEqual<float>(base, base + mathEps * 2.0f));
}

// === IsNumericallyLessOrEqual float ===

TEST(MathUtils_Float, IsNumericallyLessOrEqual_SlightlyGreater_WithinMathEpsilon)
{
    const float mathEps = DefaultTolerance<float>.mathEpsilon;
    const float base = 1.0f;
    EXPECT_TRUE(IsNumericallyLessOrEqual<float>(base, base - mathEps * 0.5f));
}

TEST(MathUtils_Float, IsNumericallyLessOrEqual_SlightlyGreater_OutsideMathEpsilon)
{
    const float mathEps = DefaultTolerance<float>.mathEpsilon;
    const float base = 1.0f;
    EXPECT_FALSE(IsNumericallyLessOrEqual<float>(base, base - mathEps * 2.0f));
}


// === IsGeometricallyZero float ===

TEST(MathUtils_Float, IsGeometricallyZero_NonZero)
{
    EXPECT_FALSE(IsGeometricallyZero<float>(3.0f));
}

TEST(MathUtils_Float, IsGeometricallyZero_Zero)
{
    EXPECT_TRUE(IsGeometricallyZero<float>(0.0f));
}

TEST(MathUtils_Float, IsGeometricallyZero_SlightlyLessThanConfusion)
{
    const float conf = DefaultTolerance<float>.geometricTolerance;
    EXPECT_TRUE(IsGeometricallyZero<float>(conf * 0.5f));
}

TEST(MathUtils_Float, IsGeometricallyZero_SlightlyMoreThanConfusion)
{
    const float conf = DefaultTolerance<float>.geometricTolerance;
    EXPECT_FALSE(IsGeometricallyZero<float>(conf * 2.0f));
}

// === AreGeometricallyEqual float ===

TEST(MathUtils_Float, AreGeometricallyEqual_DifferenceSlightlyLessThanConfusion)
{
    const float conf = DefaultTolerance<float>.geometricTolerance;
    EXPECT_TRUE(AreGeometricallyEqual<float>(1.0f, 1.0f + conf * 0.5f));
}

TEST(MathUtils_Float, AreGeometricallyEqual_DifferenceSlightlyMoreThanConfusion)
{
    const float conf = DefaultTolerance<float>.geometricTolerance;
    EXPECT_FALSE(AreGeometricallyEqual<float>(1.0f, 1.0f + conf * 2.0f));
}

TEST(MathUtils_Float, AreGeometricallyEqual_HugeValues_AbsoluteToleranceEnforced)
{
    const float conf = DefaultTolerance<float>.geometricTolerance;
    const float hugeValue = 10.0f;
    EXPECT_TRUE(AreGeometricallyEqual<float>(hugeValue, hugeValue + conf * 0.5f));
    EXPECT_FALSE(AreGeometricallyEqual<float>(hugeValue, hugeValue + conf * 2.0f));
}

// === IsGeometricallyGreaterOrEqual float ===

TEST(MathUtils_Float, IsGeometricallyGreaterOrEqual_SlightlyLess_WithinConfusion)
{
    const float conf = DefaultTolerance<float>.geometricTolerance;
    EXPECT_TRUE(IsGeometricallyGreaterOrEqual<float>(5.0f, 5.0f + conf * 0.5f));
}

TEST(MathUtils_Float, IsGeometricallyGreaterOrEqual_SlightlyLess_OutsideConfusion)
{
    const float conf = DefaultTolerance<float>.geometricTolerance;
    EXPECT_FALSE(IsGeometricallyGreaterOrEqual<float>(5.0f, 5.0f + conf * 2.0f));
}

// === IsGeometricallyLessOrEqual float ===

TEST(MathUtils_Float, IsGeometricallyLessOrEqual_SlightlyGreater_WithinConfusion)
{
    const float conf = DefaultTolerance<float>.geometricTolerance;
    EXPECT_TRUE(IsGeometricallyLessOrEqual<float>(5.0f, 5.0f - conf * 0.5f));
}

TEST(MathUtils_Float, IsGeometricallyLessOrEqual_SlightlyGreater_OutsideConfusion)
{
    const float conf = DefaultTolerance<float>.geometricTolerance;
    EXPECT_FALSE(IsGeometricallyLessOrEqual<float>(5.0f, 5.0f - conf * 2.0f));
}