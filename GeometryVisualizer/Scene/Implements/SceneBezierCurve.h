#pragma once

#include <limits>
#include <SFML/Graphics.hpp>

#include <GeometryVisualizer/Scene/Interfaces/ISceneObject.h>
#include <GeometryVisualizer/Scene/Interfaces/IInteractable.h>
#include <GeometryCore/Algorithms/PointSegmentDistance2.h>
#include <GeometryCore/Primitives/Segment2.h>
#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/BoundingVolumes/AABB2.h>    
#include <GeometryCore/Math/Utils.h>

template <typename TCoreCurve>
class SceneBezierCurve : public ISceneObject, public IInteractable
{
private:
    TCoreCurve m_coreCurve;
    int m_activeControlPointIndex = -1;
    Geometry::AABB2<float> m_bounds;

    sf::VertexArray m_drawVertices;

    size_t m_segments = 60;
    bool m_showSkeleton = true;
    bool m_showTangents = true;
    float m_tangentParam = 0.5f;
    float m_tangentScale = 0.2f;

    sf::Color m_curveColor = sf::Color(70, 180, 255);
    sf::Color m_skeletonColor = sf::Color(140, 150, 170, 200);
    sf::Color m_controlPointsColor = sf::Color(255, 195, 45);
    sf::Color m_tangentColor = sf::Color(90, 220, 120);
    float m_controlPointsThickness = 2.0f;

public:
    template<typename... Args>
    explicit SceneBezierCurve(Args&&... args) : m_coreCurve(std::forward<Args>(args)...)
    {
        Update();
    }

    ~SceneBezierCurve() override = default;

    virtual size_t GetControlPointCount() const = 0;
    virtual Geometry::Vector2<float> GetDerivativeAt(float t) const = 0;

    void Update() override
    {
        m_drawVertices.setPrimitiveType(sf::PrimitiveType::LineStrip);
        m_drawVertices.resize(m_segments + 1);

        float minX = std::numeric_limits<float>::max();
        float minY = std::numeric_limits<float>::max();
        float maxX = std::numeric_limits<float>::lowest();
        float maxY = std::numeric_limits<float>::lowest();

        for (size_t i = 0; i <= m_segments; ++i) {
            float t = static_cast<float>(i) / m_segments;

            auto pt = m_coreCurve.PointAt(t);

            m_drawVertices[i].position = sf::Vector2f(pt.x, pt.y);
            m_drawVertices[i].color = m_curveColor;

            if (pt.x < minX) minX = pt.x;
            if (pt.x > maxX) maxX = pt.x;
            if (pt.y < minY) minY = pt.y;
            if (pt.y > maxY) maxY = pt.y;
        }

        m_bounds = Geometry::AABB2<float>{
            Geometry::Point2<float>{minX, minY},
            Geometry::Point2<float>{maxX, maxY}
        };
    }

    void Release() noexcept override
    {
        IInteractable::Release();
        m_activeControlPointIndex = -1;
    }

    bool HitTest(float mousePosX, float mousePosY, float distanceThreshold) override
    {
        Geometry::Point2<float> mousePoint{ mousePosX, mousePosY };

        const size_t count = GetControlPointCount();
        constexpr float pointHitRadiusSq = 12.0f * 12.0f;

        for (size_t i = 0; i < count; ++i)
        {
            auto pt = GetControlPoint(i);
            float dx = mousePoint.x - pt.x;
            float dy = mousePoint.y - pt.y;

            if ((dx * dx + dy * dy) <= pointHitRadiusSq)
            {
                m_activeControlPointIndex = static_cast<int>(i);
                return true;
            }
        }

        m_activeControlPointIndex = -1;

        Geometry::AABB2<float> expandedBounds{
            Geometry::Point2<float>{m_bounds.min.x - distanceThreshold, m_bounds.min.y - distanceThreshold},
            Geometry::Point2<float>{m_bounds.max.x + distanceThreshold, m_bounds.max.y + distanceThreshold}
        };

        if (!expandedBounds.Contains(mousePoint))
        {
            return false;
        }

        for (size_t i = 0; i < m_segments; ++i)
        {
            Geometry::Segment2<float> seg{
                Geometry::Point2<float>{m_drawVertices[i].position.x, m_drawVertices[i].position.y},
                Geometry::Point2<float>{m_drawVertices[i + 1].position.x, m_drawVertices[i + 1].position.y}
            };
            Geometry::PointSegmentDistance2<float> pointSegmentDistanceInfo = Geometry::Distance(mousePoint, seg);

            if (Geometry::IsLessOrEqual(pointSegmentDistanceInfo.distance, distanceThreshold))
            {
                return true;
            }
        }

        return false;
    }

    void MoveTo(float mouseDeltaPosX, float mouseDeltaPosY) override
    {
        const size_t count = GetControlPointCount();

        if (m_activeControlPointIndex >= 0 &&
            m_activeControlPointIndex < static_cast<int>(count))
        {
            m_coreCurve[m_activeControlPointIndex].x += mouseDeltaPosX;
            m_coreCurve[m_activeControlPointIndex].y += mouseDeltaPosY;
        }
        else
        {
            for (size_t i = 0; i < count; ++i)
            {
                m_coreCurve[i].x += mouseDeltaPosX;
                m_coreCurve[i].y += mouseDeltaPosY;
            }
        }

        Update();
    }

    const TCoreCurve& GetCoreCurve() const { return m_coreCurve; }

    void SetControlPoint(size_t index, const Geometry::Point2<float>& pt)
    {
        m_coreCurve[index] = pt;
        Update();
    }

    [[nodiscard]] Geometry::Point2<float> GetControlPoint(size_t index) const
    {
        return m_coreCurve[index];
    }

    const sf::VertexArray& GetDrawVertices() const { return m_drawVertices; }

    [[nodiscard]] int GetSegments() const noexcept
    {
        return static_cast<int>(m_segments);
    }

    void SetSegments(int segments)
    {
        if (segments > 0)
        {
            const auto newSegments = static_cast<size_t>(segments);
            if (m_segments != newSegments)
            {
                m_segments = newSegments;
                Update();
            }
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

    sf::Color GetCurveColor() const noexcept { return m_curveColor; }
    void SetCurveColor(sf::Color c) noexcept
    {
        if (m_curveColor != c) {
            m_curveColor = c;
            Update();
        }
    }

    sf::Color GetControlPointsColor() const noexcept { return m_controlPointsColor; }
    void SetControlPointsColor(sf::Color c) noexcept { m_controlPointsColor = c; }

    sf::Color GetSkeletonColor() const noexcept { return m_skeletonColor; }
    void SetSkeletonColor(sf::Color c) noexcept { m_skeletonColor = c; }

    sf::Color GetTangentColor() const noexcept { return m_tangentColor; }
    void SetTangentColor(sf::Color c) noexcept { m_tangentColor = c; }

    float GetControlPointsThickness() const noexcept { return m_controlPointsThickness; }
    void SetControlPointsThickness(float value) noexcept { m_controlPointsThickness = value; }
};