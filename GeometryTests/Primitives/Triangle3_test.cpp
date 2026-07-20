#include "gtest/gtest.h"

#include <GeometryCore/Math/Constants.h>
#include <GeometryCore/Primitives/Triangle3.h>
#include <GeometryCore/Primitives/Point3.h>
#include <GeometryCore/Primitives/Vector3.h>
#include <GeometryCore/Math/Utils.h>

using namespace Geometry;


TEST(Triangle3D, DefaultConstructor)
{
    Triangle3<double> triangle{};

    EXPECT_DOUBLE_EQ(triangle.V0.x, 0.0);
    EXPECT_DOUBLE_EQ(triangle.V0.y, 0.0);
    EXPECT_DOUBLE_EQ(triangle.V0.z, 0.0);

    EXPECT_DOUBLE_EQ(triangle.V1.x, 0.0);
    EXPECT_DOUBLE_EQ(triangle.V1.y, 0.0);
    EXPECT_DOUBLE_EQ(triangle.V1.z, 0.0);

    EXPECT_DOUBLE_EQ(triangle.V2.x, 0.0);
    EXPECT_DOUBLE_EQ(triangle.V2.y, 0.0);
    EXPECT_DOUBLE_EQ(triangle.V2.z, 0.0);
}

TEST(Triangle3D, DefaultConstructor_CompileTime)
{
    constexpr Triangle3<double> triangle{};
    static_assert(AreEqual(triangle.V0.x, 0.0), "Compile-time failed for Triangle3");
}

TEST(Triangle3D, ParametrizedConstructor)
{
    Triangle3<double> triangle{
        Point3<double>{ 1.0, 1.0, 1.0 },
        Point3<double>{ 2.0, 2.0, 2.0 },
        Point3<double>{ 3.0, 3.0, 3.0 }
    };
    
    EXPECT_DOUBLE_EQ(triangle.V0.x, 1.0);
    EXPECT_DOUBLE_EQ(triangle.V0.y, 1.0);
    EXPECT_DOUBLE_EQ(triangle.V0.z, 1.0);

    EXPECT_DOUBLE_EQ(triangle.V1.x, 2.0);
    EXPECT_DOUBLE_EQ(triangle.V1.y, 2.0);
    EXPECT_DOUBLE_EQ(triangle.V1.z, 2.0);

    EXPECT_DOUBLE_EQ(triangle.V2.x, 3.0);
    EXPECT_DOUBLE_EQ(triangle.V2.y, 3.0);
    EXPECT_DOUBLE_EQ(triangle.V2.z, 3.0);
}

TEST(Triangle3D, ParametrizedConstructor_CompileTime)
{
    constexpr Triangle3<double> triangle{
        Point3<double>{ 1.0, 1.0, 1.0 },
        Point3<double>{ 2.0, 2.0, 2.0 },
        Point3<double>{ 3.0, 3.0, 3.0 }
    };
    static_assert(AreEqual(triangle.V0.x, 1.0), "Compile-time failed for Triangle3");
}

TEST(Triangle3D, NotDegenerate)
{
    Triangle3<double> tri(
        Point3<double>{ 1.0, 1.0, 1.0 },
        Point3<double>{ 2.0, 2.0, 2.0 },
        Point3<double>{ 3.0, 3.0, 4.0 }
    );

    EXPECT_FALSE(tri.IsDegenerate());
}

TEST(Triangle3D, NotDegenerate_XY_Plane)
{
    Triangle3<double> tri(
        Point3<double>{ 0.0, 0.0, 0.0 },
        Point3<double>{ 1.0, 0.0, 0.0 },
        Point3<double>{ 0.0, 1.0, 0.0 }
    );

    EXPECT_FALSE(tri.IsDegenerate());
}

TEST(Triangle3D, NotDegenerate_XZ_Plane)
{
    Triangle3<double> tri(
        Point3<double>{ 0.0, 0.0, 0.0 },
        Point3<double>{ 1.0, 0.0, 0.0 },
        Point3<double>{ 0.0, 0.0, 1.0 }
    );

    EXPECT_FALSE(tri.IsDegenerate());
}

TEST(Triangle3D, NotDegenerate_YZ_Plane)
{
    Triangle3<double> tri(
        Point3<double>{ 0.0, 0.0, 0.0 },
        Point3<double>{ 0.0, 1.0, 0.0 },
        Point3<double>{ 0.0, 0.0, 1.0 }
    );

    EXPECT_FALSE(tri.IsDegenerate());
}

TEST(Triangle3D, NotDegenerate_NegativeCoordinates)
{
    Triangle3<double> tri(
        Point3<double>{ -1.0, 0.0, 0.0 },
        Point3<double>{ 0.0, -1.0, 0.0 },
        Point3<double>{ 0.0, 0.0, -1.0 }
    );

    EXPECT_FALSE(tri.IsDegenerate());
}

TEST(Triangle3D, DegenerateV0InCenter)
{
    Triangle3<double> tri(
        Point3<double>(1.0, 0.0, 0.0),
        Point3<double>(0.0, 0.0, 0.0),
        Point3<double>(2.0, 0.0, 0.0)
    );

    EXPECT_TRUE(tri.IsDegenerate());
}

TEST(Triangle3D, DegenerateV1InCenter)
{
    Triangle3<double> tri(
        Point3<double>(0.0, 0.0, 0.0),
        Point3<double>(1.0, 0.0, 0.0),
        Point3<double>(2.0, 0.0, 0.0)
    );

    EXPECT_TRUE(tri.IsDegenerate());
}

TEST(Triangle3D, DegenerateV2InCenter)
{
    Triangle3<double> tri(
        Point3<double>(0.0, 0.0, 0.0),
        Point3<double>(2.0, 0.0, 0.0),
        Point3<double>(1.0, 0.0, 0.0)
    );

    EXPECT_TRUE(tri.IsDegenerate());
}

TEST(Triangle3D, DegenerateV0V1Equals)
{
    Triangle3<double> tri(
        Point3<double>(0.0, 1.0, 2.0),
        Point3<double>(0.0, 1.0, 2.0),
        Point3<double>(2.0, 5.0, 3.0)
    );

    EXPECT_TRUE(tri.IsDegenerate());
}

TEST(Triangle3D, DegenerateV0V2Equals)
{
    Triangle3<double> tri(
        Point3<double>(0.0, 1.0, 2.0),
        Point3<double>(2.0, 5.0, 3.0),
        Point3<double>(0.0, 1.0, 2.0)
    );

    EXPECT_TRUE(tri.IsDegenerate());
}

TEST(Triangle3D, DegenerateV1V2Equals)
{
    Triangle3<double> tri(
        Point3<double>(2.0, 5.0, 3.0),
        Point3<double>(0.0, 1.0, 2.0),
        Point3<double>(0.0, 1.0, 2.0)
    );

    EXPECT_TRUE(tri.IsDegenerate());
}

TEST(Triangle3D, DegenerateIntoPoint)
{
    Triangle3<double> tri(
        Point3<double>(6.0, 1.0, 2.0),
        Point3<double>(6.0, 1.0, 2.0),
        Point3<double>(6.0, 1.0, 2.0)
    );

    EXPECT_TRUE(tri.IsDegenerate());
}

TEST(Triangle3D, NotDegenerate_LargeCoordinates)
{
    Triangle3<double> tri(
        Point3<double>{ 0.0, 0.0, 0.0 },
        Point3<double>{ EPSILON<double> * 1e15, 0.0, 0.0 },
        Point3<double>{ 0.0, EPSILON<double> * 1e15 , 0.0 }
    );

    EXPECT_FALSE(tri.IsDegenerate());
}

TEST(Triangle3D, NotDegenerate_SmallButValid)
{
    Triangle3<double> tri(
        Point3<double>{ 0.0, 0.0, 0.0 },
        Point3<double>{ EPSILON<double> * 1e3, 0.0, 0.0 },
        Point3<double>{ 0.0, EPSILON<double> * 1e3, 0.0 }
    );

    EXPECT_FALSE(tri.IsDegenerate());
}

TEST(Triangle3D, Degenerate_NearlyCollinear)
{
    Triangle3<double> tri(
        Point3<double>(0.0, 0.0, 0.0),
        Point3<double>(1.0, 0.0, 0.0),
        Point3<double>(2.0, EPSILON<double> * 1e-3, 0.0)
    );

    EXPECT_TRUE(tri.IsDegenerate());
}

TEST(Triangle3D, Degenerate_LargeCoordinates)
{
    Triangle3<double> tri(
        Point3<double>(0.0, 0.0, 0.0),
        Point3<double>(EPSILON<double> *1e15, 0.0, 0.0),
        Point3<double>(EPSILON<double> *1e15, 0.0, 0.0)
    );

    EXPECT_TRUE(tri.IsDegenerate());
}

TEST(Triangle3D, NotDegenerate_TinyArea)
{
    Triangle3<double> tri(
        Point3<double>(5.0, 7.0, 8.0 + EPSILON<double>),
        Point3<double>(5.0 + EPSILON<double>, 7.0, 8.0),
        Point3<double>(5.0 - EPSILON<double>, 7.0 + EPSILON<double>, 8.0)
    );

    EXPECT_FALSE(tri.IsDegenerate());
}

TEST(Triangle3D, Degenerate_TinyArea)
{
    Triangle3<double> tri(
        Point3<double>(5.0, 7.0, 8.0 + EPSILON<double> * 1e-1),
        Point3<double>(5.0 + EPSILON<double> * 1e-1, 7.0, 8.0),
        Point3<double>(5.0 - EPSILON<double> * 1e-1, 7.0 + EPSILON<double> * 1e-1, 8.0)
    );

    EXPECT_TRUE(tri.IsDegenerate());
}