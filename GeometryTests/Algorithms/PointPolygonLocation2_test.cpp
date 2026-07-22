#include <gtest/gtest.h>
#include <GeometryCore/Algorithms/PointPolygonLocation2.h>
#include <GeometryCore/Primitives/Polygon2.h>
#include <GeometryCore/Math/Constants.h>

using namespace Geometry;

Polygon2<double> MakeSquare()
{
    return Polygon2<double>{
        {Point2<double>(0.0, 0.0),
            Point2<double>(2.0, 0.0),
            Point2<double>(2.0, 2.0),
            Point2<double>(0.0, 2.0)}
    };
}

Polygon2<double> MakeTriangle()
{
    return Polygon2<double>{
        {Point2<double>(0.0, 0.0),
            Point2<double>(4.0, 0.0),
            Point2<double>(2.0, 3.0)}
    };
}

Polygon2<double> MakeLShape()
{
    return Polygon2<double>{
        {Point2<double>(0.0, 0.0),
            Point2<double>(3.0, 0.0),
            Point2<double>(3.0, 1.0),
            Point2<double>(1.0, 1.0),
            Point2<double>(1.0, 3.0),
            Point2<double>(0.0, 3.0)}
    };
}


TEST(PointPolygonLocation2D, Inside_Square_Center)
{
    auto polygon = MakeSquare();
    Point2<double> point(1.0, 1.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Inside);
}

TEST(PointPolygonLocation2D, Inside_Triangle_Center)
{
    auto polygon = MakeTriangle();
    Point2<double> point(2.0, 1.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Inside);
}

TEST(PointPolygonLocation2D, Inside_ConcaveLShape)
{
    auto polygon = MakeLShape();
    Point2<double> point(0.5, 0.5);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Inside);
}

TEST(PointPolygonLocation2D, Inside_NearEdge)
{
    auto polygon = MakeSquare();
    Point2<double> point(0.1, 1.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Inside);
}

TEST(PointPolygonLocation2D, Outside_Square_Far)
{
    auto polygon = MakeSquare();
    Point2<double> point(5.0, 5.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Outside);
}

TEST(PointPolygonLocation2D, Outside_Square_Near)
{
    auto polygon = MakeSquare();
    Point2<double> point(2.1, 1.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Outside);
}

TEST(PointPolygonLocation2D, Outside_ConcaveLShape_InCutout)
{
    auto polygon = MakeLShape();
    Point2<double> point(2.0, 2.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Outside);
}

TEST(PointPolygonLocation2D, Outside_NegativeCoordinates)
{
    auto polygon = MakeSquare();
    Point2<double> point(-1.0, -1.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Outside);
}

TEST(PointPolygonLocation2D, OnBoundary_BottomEdge)
{
    auto polygon = MakeSquare();
    Point2<double> point(1.0, 0.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::OnBoundary);
}

TEST(PointPolygonLocation2D, OnBoundary_TopEdge)
{
    auto polygon = MakeSquare();
    Point2<double> point(1.0, 2.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::OnBoundary);
}

TEST(PointPolygonLocation2D, OnBoundary_LeftEdge)
{
    auto polygon = MakeSquare();
    Point2<double> point(0.0, 1.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::OnBoundary);
}

TEST(PointPolygonLocation2D, OnBoundary_RightEdge)
{
    auto polygon = MakeSquare();
    Point2<double> point(2.0, 1.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::OnBoundary);
}

TEST(PointPolygonLocation2D, OnBoundary_MiddleOfEdge)
{
    auto polygon = MakeTriangle();
    Point2<double> point(2.0, 0.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::OnBoundary);
}

TEST(PointPolygonLocation2D, OnBoundary_DiagonalEdge)
{
    auto polygon = MakeTriangle();
    Point2<double> point(1.0, 1.5);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::OnBoundary);
}

TEST(PointPolygonLocation2D, OnBoundary_Vertex0)
{
    auto polygon = MakeSquare();
    Point2<double> point(0.0, 0.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::OnBoundary);
}

TEST(PointPolygonLocation2D, OnBoundary_Vertex1)
{
    auto polygon = MakeSquare();
    Point2<double> point(2.0, 0.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::OnBoundary);
}

TEST(PointPolygonLocation2D, OnBoundary_Vertex2)
{
    auto polygon = MakeSquare();
    Point2<double> point(2.0, 2.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::OnBoundary);
}

TEST(PointPolygonLocation2D, OnBoundary_Vertex3)
{
    auto polygon = MakeSquare();
    Point2<double> point(0.0, 2.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::OnBoundary);
}

TEST(PointPolygonLocation2D, OnBoundary_TriangleVertex)
{
    auto polygon = MakeTriangle();
    Point2<double> point(2.0, 3.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::OnBoundary);
}

TEST(PointPolygonLocation2D, Invalid_LessThan3Vertices)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 0.0),
         Point2<double>(1.0, 0.0)}
    };
    Point2<double> point(0.5, 0.5);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Invalid);
}

TEST(PointPolygonLocation2D, Invalid_EmptyPolygon)
{
    Polygon2<double> polygon{};
    Point2<double> point(0.0, 0.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Invalid);
}

TEST(PointPolygonLocation2D, Concave_StarShape_Inside)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 2.0),
         Point2<double>(1.0, 1.0),
         Point2<double>(2.0, 2.0),
         Point2<double>(1.5, 0.5),
         Point2<double>(2.0, -1.0),
         Point2<double>(0.5, 0.0),
         Point2<double>(-2.0, -1.0),
         Point2<double>(-1.5, 0.5),
         Point2<double>(-2.0, 2.0),
         Point2<double>(-1.0, 1.0)}
    };

    Point2<double> point(0.0, 0.5);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Inside);
}

TEST(PointPolygonLocation2D, Concave_StarShape_Outside)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 2.0),
         Point2<double>(1.0, 1.0),
         Point2<double>(2.0, 2.0),
         Point2<double>(1.5, 0.5),
         Point2<double>(2.0, -1.0),
         Point2<double>(0.5, 0.0),
         Point2<double>(-2.0, -1.0),
         Point2<double>(-1.5, 0.5),
         Point2<double>(-2.0, 2.0),
         Point2<double>(-1.0, 1.0)}
    };

    Point2<double> point(1.5, 1.6);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Outside);
}

TEST(PointPolygonLocation2D, Rectangle_NonSquare)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 0.0),
         Point2<double>(4.0, 0.0),
         Point2<double>(4.0, 1.0),
         Point2<double>(0.0, 1.0)}
    };
    Point2<double> point(2.0, 0.5);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Inside);
}

TEST(PointPolygonLocation2D, NumericalStability_VerySmallPolygon)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 0.0),
         Point2<double>(1e-6, 0.0),
         Point2<double>(1e-6, 1e-6),
         Point2<double>(0.0, 1e-6)}
    };
    Point2<double> point(0.5e-6, 0.5e-6);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Inside);
}

TEST(PointPolygonLocation2D, NumericalStability_VeryLargePolygon)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 0.0),
         Point2<double>(1e6, 0.0),
         Point2<double>(1e6, 1e6),
         Point2<double>(0.0, 1e6)}
    };
    Point2<double> point(5e5, 5e5);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Inside);
}

TEST(PointPolygonLocation2D, NumericalStability_PointNearEdge)
{
    auto polygon = MakeSquare();
    Point2<double> point(1.0, EPSILON<double> *0.1);

    auto result = PointPolygonLocation(polygon, point);
    EXPECT_TRUE(result == LocationType::Inside || result == LocationType::OnBoundary);
}

TEST(PointPolygonLocation2D, NumericalStability_PointNearVertex)
{
    auto polygon = MakeSquare();
    Point2<double> point(EPSILON<double> *0.1, EPSILON<double> *0.1);

    auto result = PointPolygonLocation(polygon, point);
    EXPECT_TRUE(result == LocationType::Inside || result == LocationType::OnBoundary);
}

TEST(PointPolygonLocation2D, NegativeCoordinates_Inside)
{
    Polygon2<double> polygon{
        {Point2<double>(-3.0, -2.0),
         Point2<double>(1.0, -2.0),
         Point2<double>(1.0, 2.0),
         Point2<double>(-3.0, 2.0)}
    };
    Point2<double> point(-1.0, 0.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Inside);
}

TEST(PointPolygonLocation2D, NegativeCoordinates_Outside)
{
    Polygon2<double> polygon{
        {Point2<double>(-3.0, -2.0),
         Point2<double>(1.0, -2.0),
         Point2<double>(1.0, 2.0),
         Point2<double>(-3.0, 2.0)}
    };
    Point2<double> point(2.0, 0.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Outside);
}

TEST(PointPolygonLocation2D, NegativeCoordinates_OnBoundary)
{
    Polygon2<double> polygon{
        {Point2<double>(-3.0, -2.0),
         Point2<double>(1.0, -2.0),
         Point2<double>(1.0, 2.0),
         Point2<double>(-3.0, 2.0)}
    };
    Point2<double> point(-1.0, -2.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::OnBoundary);
}

TEST(PointPolygonLocation2D, HorizontalEdge_PointAbove)
{
    auto polygon = MakeSquare();
    Point2<double> point(1.0, 0.5);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Inside);
}

TEST(PointPolygonLocation2D, HorizontalEdge_PointBelow)
{
    auto polygon = MakeSquare();
    Point2<double> point(1.0, -0.5);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Outside);
}

TEST(PointPolygonLocation2D, VerticalEdge_PointLeft)
{
    auto polygon = MakeSquare();
    Point2<double> point(-0.5, 1.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Outside);
}

TEST(PointPolygonLocation2D, VerticalEdge_PointRight)
{
    auto polygon = MakeSquare();
    Point2<double> point(0.5, 1.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Inside);
}

TEST(PointPolygonLocation2D, ManyVertices_Circle)
{
    std::vector<Point2<double>> vertices;
    const int n = 100;
    for (int i = 0; i < n; ++i)
    {
        double angle = 2.0 * 3.14 * i / n;
        vertices.push_back(Point2<double>(std::cos(angle), std::sin(angle)));
    }

    Polygon2<double> polygon{ vertices };

    Point2<double> center(0.0, 0.0);
    EXPECT_EQ(PointPolygonLocation(polygon, center), LocationType::Inside);

    Point2<double> outside(2.0, 2.0);
    EXPECT_EQ(PointPolygonLocation(polygon, outside), LocationType::Outside);
}

TEST(PointPolygonLocation2D, CollinearVertices)
{
    Polygon2<double> polygon{
        {Point2<double>(0.0, 0.0),
         Point2<double>(1.0, 0.0),
         Point2<double>(2.0, 0.0),
         Point2<double>(2.0, 2.0),
         Point2<double>(0.0, 2.0)}
    };
    Point2<double> point(1.0, 1.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Inside);
}

TEST(PointPolygonLocation2D, PointOutsideAABB)
{
    auto polygon = MakeSquare();
    Point2<double> point(10.0, 10.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Outside);
}

TEST(PointPolygonLocation2D, PointOnAABB_ButOutsidePolygon)
{
    auto polygon = MakeLShape();
    Point2<double> point(2.0, 2.0);

    EXPECT_EQ(PointPolygonLocation(polygon, point), LocationType::Outside);
}