#pragma once

class SceneLinearBezier2;
class SceneQuadraticBezier2;
class SceneCubicBezier2;

class ISceneObjectVisitor {
public:
    virtual ~ISceneObjectVisitor() = default;

    virtual void Visit(const SceneLinearBezier2& curve) = 0;
    virtual void Visit(const SceneQuadraticBezier2& curve) = 0;
    virtual void Visit(const SceneCubicBezier2& curve) = 0;
};