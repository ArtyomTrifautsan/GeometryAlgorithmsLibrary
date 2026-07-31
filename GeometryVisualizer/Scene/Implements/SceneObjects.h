#pragma once

#include <GeometryCore/Curves/LinearBezierCurve2.h>
#include <GeometryCore/Curves/QuadraticBezierCurve2.h>
#include <GeometryCore/Curves/CubicBezierCurve2.h>

#include <GeometryVisualizer/Scene/Interfaces/ISceneObjectVisitor.h>
#include <GeometryVisualizer/Scene/Implements/SceneBezierCurve.h>

class SceneLinearBezier2 : public SceneBezierCurve<Geometry::LinearBezierCurve2<float>>
{
public:
    SceneLinearBezier2() : SceneBezierCurve(
        Geometry::LinearBezierCurve2<float>(
            Geometry::Point2<float>{300.0f, 350.0f},
            Geometry::Point2<float>{600.0f, 350.0f}
        )
    ) {}

    void Accept(ISceneObjectVisitor& visitor) override { visitor.Visit(*this); }

    std::string Name() const override { return "Linear Bezier"; }
    size_t GetControlPointCount() const override { return 2; }

    Geometry::Vector2<float> GetDerivativeAt(float t) const override
    {
        return this->GetCoreCurve().Derivative();
    }
};

class SceneQuadraticBezier2 : public SceneBezierCurve<Geometry::QuadraticBezierCurve2<float>>
{
public:
    SceneQuadraticBezier2() : SceneBezierCurve(
        Geometry::QuadraticBezierCurve2<float>(
            Geometry::Point2<float>{300.0f, 450.0f},
            Geometry::Point2<float>{450.0f, 200.0f},
            Geometry::Point2<float>{600.0f, 450.0f}
        )
    ) {}

    void Accept(ISceneObjectVisitor& visitor) override { visitor.Visit(*this); }

    std::string Name() const override { return "Quadratic Bezier"; }
    size_t GetControlPointCount() const override { return 3; }

    Geometry::Vector2<float> GetDerivativeAt(float t) const override
    {
        return this->GetCoreCurve().DerivativeAt(t);
    }
};

class SceneCubicBezier2 : public SceneBezierCurve<Geometry::CubicBezierCurve2<float>>
{
public:
    SceneCubicBezier2() : SceneBezierCurve(
        Geometry::CubicBezierCurve2<float>(
            Geometry::Point2<float>{300.0f, 450.0f},
            Geometry::Point2<float>{400.0f, 200.0f},
            Geometry::Point2<float>{500.0f, 200.0f},
            Geometry::Point2<float>{600.0f, 450.0f}
        )
    ) {}

    void Accept(ISceneObjectVisitor& visitor) override { visitor.Visit(*this); }

    std::string Name() const override { return "Cubic Bezier"; }
    size_t GetControlPointCount() const override { return 4; }

    Geometry::Vector2<float> GetDerivativeAt(float t) const override
    {
        return this->GetCoreCurve().DerivativeAt(t);
    }
};