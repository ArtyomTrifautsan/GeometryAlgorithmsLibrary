#pragma once

class SceneLinearBezier2;
class SceneQuadraticBezier2;
class SceneCubicBezier2;

class ISceneObjectVisitor {
public:
    virtual ~ISceneObjectVisitor() = default;

    virtual void Visit(SceneLinearBezier2& curve) = 0;
    virtual void Visit(SceneQuadraticBezier2& curve) = 0;
    virtual void Visit(SceneCubicBezier2& curve) = 0;
};