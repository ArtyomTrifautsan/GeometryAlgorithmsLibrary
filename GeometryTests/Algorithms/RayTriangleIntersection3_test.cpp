#include <gtest/gtest.h>

#include <GeometryCore/Algorithms/RayTriangleIntersection3.h>
#include <GeometryCore/Math/Constants.h>

using namespace Geometry;

Triangle3<double> MakeTriangleXY()
{
    return Triangle3<double>(
        Point3<double>(0.0, 0.0, 0.0),
        Point3<double>(1.0, 0.0, 0.0),
        Point3<double>(0.0, 1.0, 0.0)
    );
}

TEST(RayTriangleIntersection3D, CenterIntersection)
{
    Ray3<double> ray(Point3<double>(0.25, 0.25, -1.0), Vector3<double>(0.0, 0.0, 1.0));
    Triangle3<double> tri = MakeTriangleXY();

    auto res = Intersect(ray, tri);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.t, 1.0, EPSILON<double>);
    EXPECT_NEAR(res.point.x, 0.25, EPSILON<double>);
    EXPECT_NEAR(res.point.y, 0.25, EPSILON<double>);
    EXPECT_NEAR(res.point.z, 0.0, EPSILON<double>);
}

TEST(RayTriangleIntersection3D, IntersectionAtVertex)
{
    Ray3<double> ray(Point3<double>(0.0, 0.0, -1.0), Vector3<double>(0.0, 0.0, 1.0));
    Triangle3<double> tri = MakeTriangleXY();

    auto res = Intersect(ray, tri);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.point.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(res.point.y, 0.0, EPSILON<double>);
}

TEST(RayTriangleIntersection3D, IntersectionOnEdge)
{
    Ray3<double> ray(Point3<double>(0.5, 0.0, -1.0), Vector3<double>(0.0, 0.0, 1.0));
    Triangle3<double> tri = MakeTriangleXY();

    auto res = Intersect(ray, tri);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.point.x, 0.5, EPSILON<double>);
    EXPECT_NEAR(res.point.y, 0.0, EPSILON<double>);
}

TEST(RayTriangleIntersection3D, RayBehindTriangle)
{
    Ray3<double> ray(Point3<double>(0.25, 0.25, 1.0), Vector3<double>(0.0, 0.0, 1.0));
    Triangle3<double> tri = MakeTriangleXY();

    auto res = Intersect(ray, tri);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
}

TEST(RayTriangleIntersection3D, RayParallelToTriangle)
{
    Ray3<double> ray(Point3<double>(0.0, 0.0, 0.0), Vector3<double>(1.0, 0.0, 0.0));
    Triangle3<double> tri = MakeTriangleXY();

    auto res = Intersect(ray, tri);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
}

TEST(RayTriangleIntersection3D, RayMissesTriangle)
{
    Ray3<double> ray(Point3<double>(2.0, 2.0, -1.0), Vector3<double>(0.0, 0.0, 1.0));
    Triangle3<double> tri = MakeTriangleXY();

    auto res = Intersect(ray, tri);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
}

TEST(RayTriangleIntersection3D, VerySmallTriangle)
{
    Triangle3<double> tri(
        Point3<double>(0.0, 0.0, 0.0),
        Point3<double>(1e-6, 0.0, 0.0),
        Point3<double>(0.0, 1e-6, 0.0)
    );
    Ray3<double> ray(Point3<double>(1e-7, 1e-7, -1.0), Vector3<double>(0.0, 0.0, 1.0));

    auto res = Intersect(ray, tri);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
}

TEST(RayTriangleIntersection3D, AlmostParallelRay)
{
    Triangle3<double> tri = MakeTriangleXY();
    Ray3<double> ray(Point3<double>(0.0, 0.0, -1e-6), Vector3<double>(1.0, 0.0, 2e-6));

    auto res = Intersect(ray, tri);

    EXPECT_TRUE(res);
}

TEST(RayTriangleIntersection3D, LargeCoordinates)
{
    Triangle3<double> tri(
        Point3<double>(0.0, 0.0, 0.0),
        Point3<double>(1e6, 0.0, 0.0),
        Point3<double>(0.0, 1e6, 0.0)
    );
    Ray3<double> ray(Point3<double>(1e5, 1e5, -1e6), Vector3<double>(0.0, 0.0, 1.0));

    auto res = Intersect(ray, tri);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
}

TEST(RayTriangleIntersection3D, RayOriginOnTriangle)
{
    Ray3<double> ray(Point3<double>(0.25, 0.25, 0.0), Vector3<double>(0.0, 0.0, 1.0));
    Triangle3<double> tri = MakeTriangleXY();

    auto res = Intersect(ray, tri);

    EXPECT_TRUE(res);
    EXPECT_EQ(res.type, IntersectionType::Point);
    EXPECT_NEAR(res.t, 0.0, EPSILON<double>);
}

TEST(RayTriangleIntersection3D, DegenerateTriangleV1InCenter)
{
    Triangle3<double> tri(
        Point3<double>(0.0, 0.0, 0.0),
        Point3<double>(1.0, 0.0, 0.0),
        Point3<double>(2.0, 0.0, 0.0)
    );
    Ray3<double> ray(Point3<double>(0.5, 0.0, -1.0), Vector3<double>(0.0, 0.0, 1.0));

    auto res = Intersect(ray, tri);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
}

TEST(RayTriangleIntersection3D, DegenerateTriangleV0InCenter)
{
    Triangle3<double> tri(
        Point3<double>(1.0, 0.0, 0.0),
        Point3<double>(0.0, 0.0, 0.0),
        Point3<double>(2.0, 0.0, 0.0)
    );
    Ray3<double> ray(Point3<double>(0.5, 0.0, -1.0), Vector3<double>(0.0, 0.0, 1.0));

    auto res = Intersect(ray, tri);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
}

TEST(RayTriangleIntersection3D, DegenerateTriangleV2InCenter)
{
    Triangle3<double> tri(
        Point3<double>(1.0, 0.0, 0.0),
        Point3<double>(3.0, 0.0, 0.0),
        Point3<double>(2.0, 0.0, 0.0)
    );
    Ray3<double> ray(Point3<double>(0.5, 0.0, -1.0), Vector3<double>(0.0, 0.0, 1.0));

    auto res = Intersect(ray, tri);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
}

TEST(RayTriangleIntersection3D, DegenerateTriangleV0V1Equals)
{
    Triangle3<double> tri(
        Point3<double>(0.0, 1.0, 2.0),
        Point3<double>(0.0, 1.0, 2.0),
        Point3<double>(2.0, 5.0, 3.0)
    );
    Ray3<double> ray(Point3<double>(0.5, 0.0, -1.0), Vector3<double>(0.0, 0.0, 1.0));

    auto res = Intersect(ray, tri);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
}

TEST(RayTriangleIntersection3D, DegenerateTriangleV0V2Equals)
{
    Triangle3<double> tri(
        Point3<double>(0.0, 1.0, 2.0),
        Point3<double>(6.0, 3.0, 3.0),
        Point3<double>(0.0, 1.0, 2.0)
    );
    Ray3<double> ray(Point3<double>(0.5, 0.0, -1.0), Vector3<double>(0.0, 0.0, 1.0));

    auto res = Intersect(ray, tri);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
}

TEST(RayTriangleIntersection3D, DegenerateTriangleV1V2Equals)
{
    Triangle3<double> tri(
        Point3<double>(6.0, 1.0, 2.0),
        Point3<double>(0.0, 1.0, 2.0),
        Point3<double>(0.0, 1.0, 2.0)
    );
    Ray3<double> ray(Point3<double>(0.5, 0.0, -1.0), Vector3<double>(0.0, 0.0, 1.0));

    auto res = Intersect(ray, tri);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
}

TEST(RayTriangleIntersection3D, DegenerateTriangleIntoPoint)
{
    Triangle3<double> tri(
        Point3<double>(6.0, 1.0, 2.0),
        Point3<double>(6.0, 1.0, 2.0),
        Point3<double>(6.0, 1.0, 2.0)
    );
    Ray3<double> ray(Point3<double>(0.5, 0.0, -1.0), Vector3<double>(0.0, 0.0, 1.0));

    auto res = Intersect(ray, tri);

    EXPECT_FALSE(res);
    EXPECT_EQ(res.type, IntersectionType::None);
}