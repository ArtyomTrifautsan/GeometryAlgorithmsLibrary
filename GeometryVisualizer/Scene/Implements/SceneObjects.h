#pragma once

#include <GeometryCore/Curves/LinearBezierCurve2.h>
#include <GeometryCore/Curves/QuadraticBezierCurve2.h>
#include <GeometryCore/Curves/CubicBezierCurve2.h>

#include <GeometryVisualizer/Scene/Interfaces/ISceneObjectVisitor.h>
#include <GeometryVisualizer/Scene/Implements/SceneBezierCurve.h>

class SceneLinearBezier2 : public SceneBezierCurve<Geometry::LinearBezierCurve2<float>>
{
public:
    using SceneBezierCurve::SceneBezierCurve;

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
    using SceneBezierCurve::SceneBezierCurve;

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
    using SceneBezierCurve::SceneBezierCurve;

    void Accept(ISceneObjectVisitor& visitor) override { visitor.Visit(*this); }

    std::string Name() const override { return "Cubic Bezier"; }
    size_t GetControlPointCount() const override { return 4; }

    Geometry::Vector2<float> GetDerivativeAt(float t) const override
    {
        return this->GetCoreCurve().DerivativeAt(t);
    }
};