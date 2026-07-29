#pragma once

#include <SFML/Graphics.hpp>

#include <GeometryVisualizer/Scene/Interfaces/ISceneObject.h>
#include <GeometryVisualizer/Scene/Interfaces/IInteractable.h>
#include <GeometryCore/Curves/CubicBezierCurve2.h>
#include <GeometryCore/Primitives/Point2.h>


class SceneCubicBezierCurve2 : public ISceneObject, public IInteractable
{
private:
    Geometry::CubicBezierCurve2<float> m_coreCurve;

    sf::VertexArray m_drawVertices;

    int m_segments = 60;
    bool m_showSkeleton = true;
    bool m_showTangents = true;
    float m_tangentParam = 0.5f;
    float m_tangentScale = 0.2f;

    sf::Color m_curveСolor = sf::Color::White;
    sf::Color m_controlPointsColor = sf::Color::White;
    sf::Color m_skeletonColor = sf::Color::White;
    sf::Color m_tangentColor = sf::Color::White;

    float m_controlPointsThickness = 2.0f;

public:
    SceneCubicBezierCurve2(Geometry::Point2<float> P0,
                            Geometry::Point2<float> P1,
                            Geometry::Point2<float> P2,
                            Geometry::Point2<float> P3)
        : m_coreCurve{P0, P1, P2, P3}
    {
        Update();
    }
    ~SceneCubicBezierCurve2() override = default;

    std::string Name() const override { return "Cubic Bezier"; }
    GeometryType Type() const override { return GeometryType::CubicBezier2_t; }

    void Update() override
    {
        m_drawVertices.setPrimitiveType(sf::PrimitiveType::LineStrip);
        m_drawVertices.resize(m_segments + 1);

        for (int i = 0; i <= m_segments; ++i) {
            float t = static_cast<float>(i) / m_segments;
            auto pt = m_coreCurve.PointAt(t);
            m_drawVertices[i].position = sf::Vector2f(pt.x, pt.y);
            m_drawVertices[i].color = m_curveСolor;
        }
    }

    bool HitTest(float mousePosX, float mousePosY, float distanceThreshold) override
    {
        // Позже здесь будет алгоритм поиска расстояния до отрезков m_drawVertices
        return false;
    }

    void MoveTo(float mousePosX, float mousePosY) override
    {
        // Позже здесь будет сдвиг всех 4-х точек на (текущая_мышь - старая_мышь)
        Update(); // Не забываем обновлять после движения!
    }

    const Geometry::CubicBezierCurve2<float>& GetCoreCurve() const { return m_coreCurve; }

    void SetControlPoint(int index, const Geometry::Point2<float>& pt)
    {
        // Предполагается, что в CubicBezierCurve2 есть доступ к точкам
        // m_coreCurve.Points[index] = pt; 
        Update();
    }

    const sf::VertexArray& GetDrawVertices() const { return m_drawVertices; }

    int GetSegments() const { return m_segments; }
    void SetSegments(int segments) {
        if (m_segments != segments && segments > 0) {
            m_segments = segments;
            Update();
        }
    }

    bool GetShowSkeleton() const noexcept { return m_showSkeleton; }
    void SetShowSkeleton(bool show) noexcept { m_showSkeleton = show; }

    bool GetShowTangents() const noexcept { return m_showTangents; }
    void SetShowTangents(bool show) noexcept { m_showTangents = show; }

    float GetTangentParam() const noexcept { return m_tangentParam; }
    void SetTangentParam(float t) noexcept { m_tangentParam = t; }

    float GetTangentScale() const noexcept { return m_tangentScale; }
    void SetTangentScale(float scale) noexcept { m_tangentScale = scale; }

    sf::Color GetCurveСolor() const noexcept { return m_curveСolor; }
    void SetCurveСolor(sf::Color c) noexcept
    {
        if (m_curveСolor != c) {
            m_curveСolor = c;
            Update();
        }
    }

    sf::Color GetControlPointsСolor() const noexcept { return m_controlPointsColor; }
    void SetControlPointsСolor(sf::Color c) noexcept { m_controlPointsColor = c; }

    sf::Color GetSkeletonСolor() const noexcept { return m_skeletonColor; }
    void SetSkeletonСolor(sf::Color c) noexcept { m_skeletonColor = c; }

    sf::Color GetTangentСolor() const noexcept { return m_tangentColor; }
    void SetTangentСolor(sf::Color c) noexcept { m_tangentColor = c; }

    float GetControlPointsThickness() const noexcept { return m_controlPointsThickness; }
    void SetControlPointsThickness(float value) noexcept { m_controlPointsThickness = value; }
};