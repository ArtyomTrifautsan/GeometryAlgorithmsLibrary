#pragma once

#include <GeometryCore/Curves/LinearBezierCurve2.h>
#include <GeometryCore/Curves/QuadraticBezierCurve2.h>
#include <GeometryCore/Curves/CubicBezierCurve2.h>

#include <GeometryVisualizer/Scene/Interfaces/ISceneObjectVisitor.h>
#include <GeometryVisualizer/Scene/Implements/SceneBezierCurve.h>

class SceneLinearBezier2 : public SceneBezierCurve<Geometry::LinearBezierCurve2<float>, GeometryType::LinearBezier2_t>
{
public:
    using SceneBezierCurve::SceneBezierCurve;

    void Accept(ISceneObjectVisitor& visitor) const override {
        visitor.Visit(*this);
    }
};

class SceneQuadraticBezier2 : public SceneBezierCurve<Geometry::QuadraticBezierCurve2<float>, GeometryType::QuadraticBezier2_t>
{
public:
    using SceneBezierCurve::SceneBezierCurve;

    void Accept(ISceneObjectVisitor& visitor) const override {
        visitor.Visit(*this);
    }
};

class SceneCubicBezier2 : public SceneBezierCurve<Geometry::CubicBezierCurve2<float>, GeometryType::CubicBezier2_t>
{
public:
    using SceneBezierCurve::SceneBezierCurve;

    void Accept(ISceneObjectVisitor& visitor) const override {
        visitor.Visit(*this);
    }
};