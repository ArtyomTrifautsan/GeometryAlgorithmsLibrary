#pragma once

#include <SFML/Graphics.hpp>
#include <GeometryCore/Primitives/Point2.h>
#include <string>

class ISceneObjectVisitor;

class ISceneObject
{
public:
    virtual ~ISceneObject() = default;

    virtual std::string Name() const = 0;

    virtual void Update() = 0;

    virtual void Accept(ISceneObjectVisitor& visitor) = 0;
};