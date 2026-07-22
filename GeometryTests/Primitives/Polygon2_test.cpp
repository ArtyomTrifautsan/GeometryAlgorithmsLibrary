#include <gtest/gtest.h>

#include <cmath>

#include <GeometryCore/Primitives/Polygon2.h>
#include <GeometryCore/BoundingVolumes/AABB2.h>
#include <GeometryCore/Math/Constants.h>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace Geometry;


TEST(Polygon2Bounds, Square)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 0.0),
         Point2<double>(2.0, 0.0),
         Point2<double>(2.0, 2.0),
         Point2<double>(0.0, 2.0)}
    };

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(bounds.min.y, 0.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.x, 2.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.y, 2.0, EPSILON<double>);
}

TEST(Polygon2Bounds, Triangle)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 0.0),
         Point2<double>(3.0, 0.0),
         Point2<double>(1.5, 2.0)}
    };

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(bounds.min.y, 0.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.x, 3.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.y, 2.0, EPSILON<double>);
}

TEST(Polygon2Bounds, Rectangle)
{
    Polygon2<double> polygon{
        {Point2<double>(1.0, 2.0),
         Point2<double>(5.0, 2.0),
         Point2<double>(5.0, 4.0),
         Point2<double>(1.0, 4.0)}
    };

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(bounds.min.y, 2.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.x, 5.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.y, 4.0, EPSILON<double>);
}

TEST(Polygon2Bounds, NegativeCoordinates)
{
    Polygon2<double> polygon{
        {Point2<double>(-3.0, -2.0),
         Point2<double>(1.0, -2.0),
         Point2<double>(1.0, 2.0),
         Point2<double>(-3.0, 2.0)}
    };

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, -3.0, EPSILON<double>);
    EXPECT_NEAR(bounds.min.y, -2.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.y, 2.0, EPSILON<double>);
}

TEST(Polygon2Bounds, AllNegativeCoordinates)
{
    Polygon2<double> polygon{
        {Point2<double>(-5.0, -5.0),
         Point2<double>(-1.0, -5.0),
         Point2<double>(-1.0, -1.0),
         Point2<double>(-5.0, -1.0)}
    };

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, -5.0, EPSILON<double>);
    EXPECT_NEAR(bounds.min.y, -5.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.x, -1.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.y, -1.0, EPSILON<double>);
}

TEST(Polygon2Bounds, ConcaveLShape)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 0.0),
         Point2<double>(3.0, 0.0),
         Point2<double>(3.0, 1.0),
         Point2<double>(1.0, 1.0),
         Point2<double>(1.0, 3.0),
         Point2<double>(0.0, 3.0)}
    };

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(bounds.min.y, 0.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.x, 3.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.y, 3.0, EPSILON<double>);
}

TEST(Polygon2Bounds, ConcaveStar)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 2.0),
         Point2<double>(1.0, 1.0),
         Point2<double>(2.0, 2.0),
         Point2<double>(1.5, 0.5),
         Point2<double>(2.0, -1.0),
         Point2<double>(0.5, 0.0),
         Point2<double>(-1.0, -1.0),
         Point2<double>(-0.5, 0.5),
         Point2<double>(-2.0, 2.0),
         Point2<double>(-1.0, 1.0)}
    };

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, -2.0, EPSILON<double>);
    EXPECT_NEAR(bounds.min.y, -1.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.x, 2.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.y, 2.0, EPSILON<double>);
}

TEST(Polygon2Bounds, EmptyPolygon)
{
    Polygon2<double> polygon{};

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(bounds.min.y, 0.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.y, 0.0, EPSILON<double>);
}

TEST(Polygon2Bounds, LessThanThreeVertices)
{
    Polygon2<double> polygon{
        {Point2<double>(1.0, 2.0),
         Point2<double>(3.0, 4.0)}
    };

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, 1.0, EPSILON<double>);
    EXPECT_NEAR(bounds.min.y, 2.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.x, 3.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.y, 4.0, EPSILON<double>);
}

TEST(Polygon2Bounds, SingleVertex)
{
    Polygon2<double> polygon{
        {Point2<double>(5.0, 5.0)}
    };

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, 5.0, EPSILON<double>);
    EXPECT_NEAR(bounds.min.y, 5.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.x, 5.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.y, 5.0, EPSILON<double>);
}

TEST(Polygon2Bounds, VeryLargeCoordinates)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 0.0),
         Point2<double>(1e6, 0.0),
         Point2<double>(1e6, 1e6),
         Point2<double>(0.0, 1e6)}
    };

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, 0.0, 1e-3);
    EXPECT_NEAR(bounds.min.y, 0.0, 1e-3);
    EXPECT_NEAR(bounds.max.x, 1e6, 1e-3);
    EXPECT_NEAR(bounds.max.y, 1e6, 1e-3);
}

TEST(Polygon2Bounds, VerySmallCoordinates)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 0.0),
         Point2<double>(1e-6, 0.0),
         Point2<double>(1e-6, 1e-6),
         Point2<double>(0.0, 1e-6)}
    };

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, 0.0, 1e-12);
    EXPECT_NEAR(bounds.min.y, 0.0, 1e-12);
    EXPECT_NEAR(bounds.max.x, 1e-6, 1e-12);
    EXPECT_NEAR(bounds.max.y, 1e-6, 1e-12);
}

TEST(Polygon2Bounds, ManyVertices)
{
    std::vector<Point2<double>> vertices;
    const int n = 100;
    for (int i = 0; i < n; ++i)
    {
        double angle = 2.0 * 3.14 * i / n;
        vertices.push_back(Point2<double>(std::cos(angle), std::sin(angle)));
    }

    Polygon2<double> polygon{ vertices };

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, -1.0, 0.1);
    EXPECT_NEAR(bounds.min.y, -1.0, 0.1);
    EXPECT_NEAR(bounds.max.x, 1.0, 0.1);
    EXPECT_NEAR(bounds.max.y, 1.0, 0.1);
}

TEST(Polygon2Bounds, CollinearVertices)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 0.0),
         Point2<double>(1.0, 0.0),
         Point2<double>(2.0, 0.0),
         Point2<double>(2.0, 2.0),
         Point2<double>(0.0, 2.0)}
    };

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(bounds.min.y, 0.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.x, 2.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.y, 2.0, EPSILON<double>);
}

TEST(Polygon2Bounds, DuplicateVertices)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 0.0),
         Point2<double>(0.0, 0.0),
         Point2<double>(2.0, 0.0),
         Point2<double>(2.0, 2.0),
         Point2<double>(0.0, 2.0)}
    };

    const AABB2<double>& bounds = polygon.GetBounds();

    EXPECT_NEAR(bounds.min.x, 0.0, EPSILON<double>);
    EXPECT_NEAR(bounds.min.y, 0.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.x, 2.0, EPSILON<double>);
    EXPECT_NEAR(bounds.max.y, 2.0, EPSILON<double>);
}