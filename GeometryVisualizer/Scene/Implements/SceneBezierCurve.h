#pragma once

#include <SFML/Graphics.hpp>

#include <GeometryVisualizer/Scene/Interfaces/ISceneObject.h>
#include <GeometryVisualizer/Scene/Interfaces/IInteractable.h>
#include <GeometryCore/Algorithms/PointSegmentDistance2.h>
#include <GeometryCore/Primitives/Segment2.h>
#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/BoundingVolumes/AABB2.h>    
#include <GeometryCore/Math/Utils.h>


template <typename TCoreCurve, GeometryType TGeoType>
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
    SceneBezierCurve(Args&&... args) : m_coreCurve(std::forward<Args>(args)...)
    {
        Update();
    }

    ~SceneBezierCurve() override = default;

    std::string Name() const override
    {
        if constexpr (TGeoType == GeometryType::CubicBezier2_t) return "Cubic Bezier";
        if constexpr (TGeoType == GeometryType::QuadraticBezier2_t) return "Quadratic Bezier";
        if constexpr (TGeoType == GeometryType::LinearBezier2_t) return "Linear Bezier";
        return "Unknown Bezier";
    }

    GeometryType Type() const override { return TGeoType; }

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

    //void Draw(sf::RenderTarget& target) const override
    //{
    //    //auto p = GetControlPoint(0);
    //    //std::cout << "Drawing! Point 0: (" << p.x << ", " << p.y
    //    //    << ") | Vertices: " << m_drawVertices.getVertexCount() << "\n";

    //    // Определяем, взаимодействует ли пользователь с объектом
    //    const bool isInteracted = (State() == InteractedState::Selected || State() == InteractedState::Dragged);

    //    // --- 1. Отрисовка сама кривая ---
    //    if (isInteracted)
    //    {
    //        // При выделении/перетаскивании рисуем подложку-свечение и утолщенную линию
    //        DrawThickLineStrip(target, m_drawVertices, 6.0f, sf::Color(255, 255, 255, 90)); // Мягкий полупрозрачный контур
    //        DrawThickLineStrip(target, m_drawVertices, 3.5f, m_curveColor);                  // Основная утолщенная линия
    //    }
    //    else
    //    {
    //        // Обычная тонкая кривая в 1px
    //        target.draw(m_drawVertices);
    //    }

    //    // --- 2. Отрисовка скелета и опорных точек ---
    //    if (m_showSkeleton)
    //    {
    //        constexpr size_t pointCount = GetControlPointCount();

    //        // 2.1 Ломаная скелета
    //        sf::VertexArray skeleton(sf::PrimitiveType::LineStrip, pointCount);
    //        for (size_t i = 0; i < pointCount; ++i)
    //        {
    //            auto pt = GetControlPoint(i);
    //            skeleton[i] = sf::Vertex(sf::Vector2f(pt.x, pt.y), m_skeletonColor);
    //        }

    //        if (isInteracted) {
    //            DrawThickLineStrip(target, skeleton, 2.0f, m_skeletonColor);
    //        }
    //        else {
    //            target.draw(skeleton);
    //        }

    //        // 2.2. Контрольные точки
    //        float pointRadius = isInteracted ? 7.5f : 4.5f;
    //        float outlineThickness = isInteracted ? 2.5f : 1.5f;

    //        sf::CircleShape pointMarker(pointRadius);
    //        pointMarker.setOrigin(sf::Vector2f(pointRadius, pointRadius));
    //        pointMarker.setFillColor(isInteracted ? sf::Color(255, 220, 50) : m_controlPointsColor);
    //        pointMarker.setOutlineThickness(outlineThickness);
    //        pointMarker.setOutlineColor(isInteracted ? sf::Color::White : sf::Color(20, 20, 22));

    //        for (size_t i = 0; i < pointCount; ++i)
    //        {
    //            auto pt = GetControlPoint(i);
    //            pointMarker.setPosition(sf::Vector2f(pt.x, pt.y));

    //            // Подсвечиваем перетаскиваемую точку
    //            if (isInteracted && static_cast<int>(i) == m_activeControlPointIndex)
    //            {
    //                pointMarker.setRadius(9.5f);
    //                pointMarker.setOrigin(sf::Vector2f(9.5f, 9.5f));
    //                pointMarker.setFillColor(sf::Color(255, 90, 40)); // Ярко-оранжевый
    //                pointMarker.setOutlineColor(sf::Color::White);

    //                target.draw(pointMarker);

    //                // Возвращаем дефолтные параметры маркеру
    //                pointMarker.setRadius(pointRadius);
    //                pointMarker.setOrigin(sf::Vector2f(pointRadius, pointRadius));
    //                pointMarker.setFillColor(sf::Color(255, 220, 50));
    //            }
    //            else
    //            {
    //                target.draw(pointMarker);
    //            }
    //        }
    //    }

    //    // --- 3. Отрисовка касательного вектора со стрелочкой ---
    //    if (m_showTangents)
    //    {
    //        auto pt = m_coreCurve.PointAt(m_tangentParam);

    //        Geometry::Vector2<float> deriv{};
    //        if constexpr (TGeoType == GeometryType::LinearBezier2_t)
    //        {
    //            deriv = m_coreCurve.Derivative();
    //        }
    //        else
    //        {
    //            deriv = m_coreCurve.DerivativeAt(m_tangentParam);
    //        }

    //        sf::Vector2f startPos(pt.x, pt.y);
    //        sf::Vector2f endPos(pt.x + deriv.x * m_tangentScale, pt.y + deriv.y * m_tangentScale);

    //        sf::Vector2f dir = endPos - startPos;
    //        float length = std::hypot(dir.x, dir.y);

    //        if (length > 0.001f)
    //        {
    //            sf::Vector2f u = dir / length;
    //            sf::Vector2f p(-u.y, u.x);

    //            constexpr float arrowLength = 10.0f;
    //            constexpr float arrowWidth = 5.0f;

    //            sf::Vector2f arrowBase = endPos - u * arrowLength;
    //            sf::Vector2f wing1 = arrowBase + p * arrowWidth;
    //            sf::Vector2f wing2 = arrowBase - p * arrowWidth;

    //            sf::VertexArray tangentLine(sf::PrimitiveType::Lines, 6);

    //            tangentLine[0] = sf::Vertex(startPos, m_tangentColor);
    //            tangentLine[1] = sf::Vertex(endPos, m_tangentColor);

    //            tangentLine[2] = sf::Vertex(endPos, m_tangentColor);
    //            tangentLine[3] = sf::Vertex(wing1, m_tangentColor);

    //            tangentLine[4] = sf::Vertex(endPos, m_tangentColor);
    //            tangentLine[5] = sf::Vertex(wing2, m_tangentColor);

    //            target.draw(tangentLine);
    //        }

    //        constexpr float tangentRadius = 3.0f;
    //        sf::CircleShape tangentMarker(tangentRadius);
    //        tangentMarker.setOrigin(sf::Vector2f(tangentRadius, tangentRadius));
    //        tangentMarker.setFillColor(m_tangentColor);
    //        tangentMarker.setPosition(startPos);
    //        target.draw(tangentMarker);
    //    }
    //}

    void Release() noexcept override
    {
        IInteractable::Release();
        m_activeControlPointIndex = -1; // Сбрасываем выбор точки
    }

    bool HitTest(float mousePosX, float mousePosY, float distanceThreshold) override
    {
        Geometry::Point2<float> mousePoint{ mousePosX, mousePosY };

        constexpr size_t count = GetControlPointCount();
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

    //bool HitTest(float mousePosX, float mousePosY, float distanceThreshold) override
    //{
    //    Geometry::Point2<float> mousePoint{ mousePosX, mousePosY };

    //    // 1. Печатаем клик и границы кривой
    //    std::cout << "[HitTest] Mouse: (" << mousePosX << ", " << mousePosY << ")"
    //        << " | AABB min: (" << m_bounds.min.x << ", " << m_bounds.min.y << ")"
    //        << " max: (" << m_bounds.max.x << ", " << m_bounds.max.y << ")\n";

    //    Geometry::AABB2<float> expandedBounds{
    //        Geometry::Point2<float>{m_bounds.min.x - distanceThreshold, m_bounds.min.y - distanceThreshold},
    //        Geometry::Point2<float>{m_bounds.max.x + distanceThreshold, m_bounds.max.y + distanceThreshold}
    //    };

    //    if (!expandedBounds.Contains(mousePoint))
    //    {
    //        std::cout << "  -> Failed AABB check!\n";
    //        return false;
    //    }

    //    // 2. Проверка точного расстояния
    //    float minDistanceFound = std::numeric_limits<float>::max();

    //    for (size_t i = 0; i < m_segments; ++i)
    //    {
    //        Geometry::Segment2<float> seg{
    //            Geometry::Point2<float>{m_drawVertices[i].position.x, m_drawVertices[i].position.y},
    //            Geometry::Point2<float>{m_drawVertices[i + 1].position.x, m_drawVertices[i + 1].position.y}
    //        };

    //        auto distInfo = Geometry::Distance(mousePoint, seg);
    //        if (distInfo.distance < minDistanceFound) {
    //            minDistanceFound = distInfo.distance;
    //        }

    //        if (Geometry::IsLessOrEqual(distInfo.distance, distanceThreshold))
    //        {
    //            std::cout << "  -> SUCCESS! Distance: " << distInfo.distance << "\n";
    //            return true;
    //        }
    //    }

    //    std::cout << "  -> Failed segment distance check. Closest segment was: " << minDistanceFound << " px away (threshold was " << distanceThreshold << ")\n";
    //    return false;
    //}

    void MoveTo(float mouseDeltaPosX, float mouseDeltaPosY) override
    {
        constexpr size_t count = GetControlPointCount();

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

public:
    static constexpr size_t GetControlPointCount() noexcept
    {
        if constexpr (TGeoType == GeometryType::LinearBezier2_t) return 2;
        else if constexpr (TGeoType == GeometryType::QuadraticBezier2_t) return 3;
        else if constexpr (TGeoType == GeometryType::CubicBezier2_t) return 4;
        return 0;
    }

private:
    //void DrawThickLineStrip(sf::RenderTarget& target,
    //    const sf::VertexArray& vertices,
    //    float thickness,
    //    sf::Color color) const
    //{
    //    if (vertices.getVertexCount() < 2) return;

    //    float halfThickness = thickness * 0.5f;
    //    sf::VertexArray quads(sf::PrimitiveType::Triangles, (vertices.getVertexCount() - 1) * 6);
    //    size_t vertexIdx = 0;

    //    for (size_t i = 0; i < vertices.getVertexCount() - 1; ++i)
    //    {
    //        sf::Vector2f a = vertices[i].position;
    //        sf::Vector2f b = vertices[i + 1].position;

    //        sf::Vector2f dir = b - a;
    //        float len = std::hypot(dir.x, dir.y);
    //        if (len < 0.001f) continue;

    //        // Единичная нормаль к отрезку
    //        sf::Vector2f normal(-dir.y / len, dir.x / len);
    //        sf::Vector2f offset = normal * halfThickness;

    //        // 4 вершины прямоугольника
    //        sf::Vector2f v0 = a + offset;
    //        sf::Vector2f v1 = a - offset;
    //        sf::Vector2f v2 = b + offset;
    //        sf::Vector2f v3 = b - offset;

    //        // Первый треугольник
    //        quads[vertexIdx++] = sf::Vertex(v0, color);
    //        quads[vertexIdx++] = sf::Vertex(v1, color);
    //        quads[vertexIdx++] = sf::Vertex(v2, color);

    //        // Второй треугольник
    //        quads[vertexIdx++] = sf::Vertex(v2, color);
    //        quads[vertexIdx++] = sf::Vertex(v1, color);
    //        quads[vertexIdx++] = sf::Vertex(v3, color);
    //    }

    //    target.draw(quads);
    //}
};