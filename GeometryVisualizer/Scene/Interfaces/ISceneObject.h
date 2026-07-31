#pragma once

#include <SFML/Graphics.hpp>
#include <GeometryCore/Primitives/Point2.h>
#include <string>

enum class GeometryType
{
    LinearBezier2_t,
    QuadraticBezier2_t,
    CubicBezier2_t
};

class ISceneObject {
public:
    virtual ~ISceneObject() = default;

    virtual std::string Name() const = 0;
    virtual GeometryType Type() const = 0;

    virtual void Update() = 0;
};