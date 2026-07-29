#pragma once

#include <GeometryCore/Curves/LinearBezierCurve2.h>
#include <GeometryCore/Curves/QuadraticBezierCurve2.h>
#include <GeometryCore/Curves/CubicBezierCurve2.h>

#include "SceneBezierCurve.h" 

using SceneLinearBezier2 = SceneBezierCurve<
    Geometry::LinearBezierCurve2<float>,
    GeometryType::LinearBezier2_t
>;

using SceneQuadraticBezier2 = SceneBezierCurve<
    Geometry::QuadraticBezierCurve2<float>,
    GeometryType::QuadraticBezier2_t
>;

using SceneCubicBezier2 = SceneBezierCurve<
    Geometry::CubicBezierCurve2<float>,
    GeometryType::CubicBezier2_t
>;