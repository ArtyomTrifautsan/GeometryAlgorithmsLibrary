#pragma once
#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

#include <GeometryVisualizer/Scene/SceneContext.h>
#include <GeometryVisualizer/Scene/Implements/SceneObjects.h>

class SceneRenderer : public ISceneObjectVisitor
{
private:
    sf::RenderTarget* m_currentTarget = nullptr;

public:
    void Render(const SceneContext& context, sf::RenderTarget& target)
    {
        target.setView(target.getDefaultView());
        m_currentTarget = &target;

        for (const auto& objPtr : context.GetObjects())
        {
            if (objPtr) {
                objPtr->Accept(*this);
            }
        }

        m_currentTarget = nullptr;
    }

    void Visit(SceneLinearBezier2& curve) override
    {
        if (m_currentTarget) RenderCurve(&curve, *m_currentTarget);
    }
    void Visit(SceneQuadraticBezier2& curve) override
    {
        if (m_currentTarget) RenderCurve(&curve, *m_currentTarget);
    }
    void Visit(SceneCubicBezier2& curve) override
    {
        if (m_currentTarget) RenderCurve(&curve, *m_currentTarget);
    }

private:
    template <typename TCore>
    void RenderCurve(const SceneBezierCurve<TCore>* curve, sf::RenderTarget& target)
    {
        const bool isInteracted = (curve->State() == InteractedState::Selected ||
            curve->State() == InteractedState::Dragged);

        const auto& vertices = curve->GetDrawVertices();

        if (vertices.getVertexCount() < 2) return;

        // --- 1. Draw the curve ---
        if (isInteracted)
        {
            DrawThickLineStrip(target, vertices, 6.0f, sf::Color(255, 255, 255, 90));
            DrawThickLineStrip(target, vertices, 3.5f, curve->GetCurveColor());
        }
        else
        {
            target.draw(vertices);
        }

        // --- 2. Draw the skeleton and the pivots ---
        if (curve->GetShowSkeleton())
        {
            // Skeleton
            const size_t pointCount = curve->GetControlPointCount();

            sf::VertexArray skeleton(sf::PrimitiveType::LineStrip, pointCount);
            for (size_t i = 0; i < pointCount; ++i)
            {
                auto pt = curve->GetControlPoint(i);
                skeleton[i] = sf::Vertex(sf::Vector2f(pt.x, pt.y), curve->GetSkeletonColor());
            }

            if (isInteracted) {
                DrawThickLineStrip(target, skeleton, 2.0f, curve->GetSkeletonColor());
            }
            else {
                target.draw(skeleton);
            }

            // Pivots
            float pointRadius = isInteracted ? 7.5f : 4.5f;
            float outlineThickness = isInteracted ? 2.5f : 1.5f;

            sf::CircleShape pointMarker(pointRadius);
            pointMarker.setOrigin(sf::Vector2f(pointRadius, pointRadius));
            pointMarker.setFillColor(isInteracted ? sf::Color(255, 220, 50) : curve->GetControlPointsColor());
            pointMarker.setOutlineThickness(outlineThickness);
            pointMarker.setOutlineColor(isInteracted ? sf::Color::White : sf::Color(20, 20, 22));

            for (size_t i = 0; i < pointCount; ++i)
            {
                auto pt = curve->GetControlPoint(i);
                pointMarker.setPosition(sf::Vector2f(pt.x, pt.y));
                target.draw(pointMarker);
            }
        }

        // --- 3. Draw Tangent Vector ---
        if (curve->GetShowTangents())
        {
            float t = curve->GetTangentParam();
            const auto& coreCurve = curve->GetCoreCurve();

            auto pt = coreCurve.PointAt(t);
            sf::Vector2f startPos(pt.x, pt.y);

            Geometry::Vector2<float> deriv = curve->GetDerivativeAt(t);

            if (!deriv.Zero())
            {
                deriv.Normalize();

                float fixedLength = 60.0f * curve->GetTangentScale();

                Geometry::Vector2<float> scaledDeriv = deriv * fixedLength;

                sf::Vector2f endPos = startPos + sf::Vector2f(scaledDeriv.x, scaledDeriv.y);

                sf::Color tColor = curve->GetTangentColor();
                sf::VertexArray tangentLine(sf::PrimitiveType::Lines, 6);

                tangentLine[0] = sf::Vertex(startPos, tColor);
                tangentLine[1] = sf::Vertex(endPos, tColor);

                constexpr float arrowLength = 12.0f;
                constexpr float arrowWidth = 5.0f;

                sf::Vector2f dir(deriv.x, deriv.y);
                sf::Vector2f p(-deriv.y, deriv.x);

                sf::Vector2f arrowBase = endPos - dir * arrowLength;
                sf::Vector2f wing1 = arrowBase + p * arrowWidth;
                sf::Vector2f wing2 = arrowBase - p * arrowWidth;

                tangentLine[2] = sf::Vertex(endPos, tColor);
                tangentLine[3] = sf::Vertex(wing1, tColor);
                tangentLine[4] = sf::Vertex(endPos, tColor);
                tangentLine[5] = sf::Vertex(wing2, tColor);

                target.draw(tangentLine);
            }

            constexpr float tangentRadius = 4.0f;
            sf::CircleShape tangentMarker(tangentRadius);
            tangentMarker.setOrigin(sf::Vector2f(tangentRadius, tangentRadius));
            tangentMarker.setFillColor(curve->GetTangentColor());
            tangentMarker.setOutlineThickness(1.5f);
            tangentMarker.setOutlineColor(sf::Color(20, 20, 22));
            tangentMarker.setPosition(startPos);
            target.draw(tangentMarker);
        }
    }

    void DrawThickLineStrip(sf::RenderTarget& target,
                            const sf::VertexArray& vertices,
                            float thickness,
                            sf::Color color) const
    {
        if (vertices.getVertexCount() < 2) return;

        float halfThickness = thickness * 0.5f;
        sf::VertexArray quads(sf::PrimitiveType::Triangles, (vertices.getVertexCount() - 1) * 6);
        size_t vertexIdx = 0;

        for (size_t i = 0; i < vertices.getVertexCount() - 1; ++i)
        {
            sf::Vector2f a = vertices[i].position;
            sf::Vector2f b = vertices[i + 1].position;

            sf::Vector2f dir = b - a;
            float len = std::hypot(dir.x, dir.y);
            if (len < 0.001f) continue;

            sf::Vector2f normal(-dir.y / len, dir.x / len);
            sf::Vector2f offset = normal * halfThickness;

            sf::Vector2f v0 = a + offset;
            sf::Vector2f v1 = a - offset;
            sf::Vector2f v2 = b + offset;
            sf::Vector2f v3 = b - offset;

            quads[vertexIdx++] = sf::Vertex(v0, color);
            quads[vertexIdx++] = sf::Vertex(v1, color);
            quads[vertexIdx++] = sf::Vertex(v2, color);
            quads[vertexIdx++] = sf::Vertex(v2, color);
            quads[vertexIdx++] = sf::Vertex(v1, color);
            quads[vertexIdx++] = sf::Vertex(v3, color);
        }
        target.draw(quads);
    }
};