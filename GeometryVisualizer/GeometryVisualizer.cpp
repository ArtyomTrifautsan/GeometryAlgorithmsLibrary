#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <cmath>
#include <vector>

#include <GeometryCore/Primitives/Point2.h>
#include <GeometryCore/Primitives/Vector2.h>
#include <GeometryCore/Curves/LinearBezierCurve2.h>
#include <GeometryCore/Curves/QuadraticBezierCurve2.h>
#include <GeometryCore/Curves/CubicBezierCurve2.h>

using Pointf = Geometry::Point2<float>;
using Vectorf = Geometry::Vector2<float>;

// -----------------------------------------------------------------------------
// Вспомогательные функции отрисовки
// -----------------------------------------------------------------------------

void DrawLine(sf::RenderWindow& window, const Pointf& p0, const Pointf& p1, sf::Color color)
{
    sf::Vertex line[] = {
        sf::Vertex({ p0.x, p0.y }, color),
        sf::Vertex({ p1.x, p1.y }, color)
    };
    window.draw(line, 2, sf::PrimitiveType::Lines);
}

void DrawArrow(sf::RenderWindow& window, const Pointf& origin, const Vectorf& vec, sf::Color color, float headLength = 12.0f, float headAngleDeg = 25.0f)
{
    Pointf target = origin + vec;

    DrawLine(window, origin, target, color);

    float lenSq = vec.x * vec.x + vec.y * vec.y;
    if (lenSq < 1e-5f) return;

    float angle = std::atan2(vec.y, vec.x);
    float rad1 = angle + 3.14159265f - (headAngleDeg * 3.14159265f / 180.0f);
    float rad2 = angle + 3.14159265f + (headAngleDeg * 3.14159265f / 180.0f);

    Pointf wing1 = target + Vectorf{ std::cos(rad1) * headLength, std::sin(rad1) * headLength };
    Pointf wing2 = target + Vectorf{ std::cos(rad2) * headLength, std::sin(rad2) * headLength };

    DrawLine(window, target, wing1, color);
    DrawLine(window, target, wing2, color);
}

void DrawControlPoint(sf::RenderWindow& window, const Pointf& pt, sf::Color color, float radius = 7.0f, bool isHoveredOrDragged = false)
{
    sf::CircleShape shape(isHoveredOrDragged ? radius * 1.4f : radius);
    shape.setOrigin({ shape.getRadius(), shape.getRadius() });
    shape.setPosition({ pt.x, pt.y });
    shape.setFillColor(color);
    shape.setOutlineThickness(2.0f);
    shape.setOutlineColor(sf::Color::White);
    window.draw(shape);
}

template <typename Curve>
void DrawBezierCurve(sf::RenderWindow& window, const Curve& curve, int segments, sf::Color color)
{
    sf::VertexArray va(sf::PrimitiveType::LineStrip, segments + 1);
    for (int i = 0; i <= segments; ++i)
    {
        float t = static_cast<float>(i) / segments;
        Pointf p = curve.PointAt(t);
        va[i].position = sf::Vector2f(p.x, p.y);
        va[i].color = color;
    }
    window.draw(va);
}

// -----------------------------------------------------------------------------
// Точка входа
// -----------------------------------------------------------------------------

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Bezier Curves Interacting");
    window.setFramerateLimit(60);

    if (!ImGui::SFML::Init(window))
        return -1;

    sf::Clock deltaClock;

    // Контрольные точки
    Pointf p0{ 200.0f, 500.0f };
    Pointf p1{ 400.0f, 150.0f };
    Pointf p2{ 800.0f, 150.0f };
    Pointf p3{ 1000.0f, 500.0f };

    int curveType = 2;       // 0 - Linear, 1 - Quadratic, 2 - Cubic
    int segments = 60;
    bool showSkeleton = true;
    bool showTangents = true;
    float tangentParam = 0.5f;
    float tangentScale = 0.2f;

    // Интерактивность
    int draggedPointIndex = -1;
    const float grabRadius = 15.0f;

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
                window.close();
        }

        sf::Time dt = deltaClock.restart();
        ImGui::SFML::Update(window, dt);

        // =========================================================================
        // 1. СНАЧАЛА СТРОИМ ИНТЕРФЕЙС IMGUI (Чтобы ImGui посчитал свой WantCaptureMouse)
        // =========================================================================
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::Begin("Bezier Curve Controls", nullptr, flags);
        ImGui::Combo("Curve Type", &curveType, "Linear\0Quadratic\0Cubic\0");
        ImGui::SliderInt("Quality (Segments)", &segments, 5, 200);
        ImGui::Checkbox("Show Control Skeleton", &showSkeleton);
        ImGui::Checkbox("Show Tangent Vector", &showTangents);

        if (showTangents)
        {
            ImGui::SliderFloat("Tangent t", &tangentParam, 0.0f, 1.0f);
            ImGui::SliderFloat("Vector Scale", &tangentScale, 0.01f, 1.0f);
        }

        ImGui::Separator();
        ImGui::Text("Control Points (Drag with mouse):");
        ImGui::DragFloat2("P0", &p0.x, 1.0f);
        ImGui::DragFloat2("P1", &p1.x, 1.0f);
        if (curveType >= 1) ImGui::DragFloat2("P2", &p2.x, 1.0f);
        if (curveType == 2) ImGui::DragFloat2("P3", &p3.x, 1.0f);
        ImGui::End();

        // =========================================================================
        // 2. ТЕПЕРЬ ОБРАБАТЫВАЕМ МЫШЬ ДЛЯ СЦЕНЫ
        // =========================================================================
        sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        Pointf mousePos{ mouseWorld.x, mouseWorld.y };

        std::vector<Pointf*> activePoints = { &p0, &p1 };
        if (curveType >= 1) activePoints.push_back(&p2);
        if (curveType == 2) activePoints.push_back(&p3);

        // Запрашиваем точное состояние ImGui ПОСЛЕ построения GUI
        bool isMouseOverGui = ImGui::GetIO().WantCaptureMouse;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            // Если точка УЖЕ захвачена — ведем ее следом за мышью
            if (draggedPointIndex != -1)
            {
                if (draggedPointIndex < static_cast<int>(activePoints.size()))
                {
                    *activePoints[draggedPointIndex] = mousePos;
                }
            }
            // Если кликнули МИМО GUI — ищем точку для захвата
            else if (!isMouseOverGui)
            {
                for (size_t i = 0; i < activePoints.size(); ++i)
                {
                    Vectorf diff = mousePos - *activePoints[i];
                    if (diff.x * diff.x + diff.y * diff.y <= grabRadius * grabRadius)
                    {
                        draggedPointIndex = static_cast<int>(i);
                        *activePoints[draggedPointIndex] = mousePos;
                        break;
                    }
                }
            }
        }
        else
        {
            draggedPointIndex = -1; // Отпустили кнопку мыши — сбрасываем захват
        }

        // =========================================================================
        // 3. РЕНДЕРИНГ СЦЕНЫ
        // =========================================================================
        window.clear(sf::Color(30, 30, 30));

        auto DrawPoints = [&](const std::vector<Pointf*>& pts) {
            for (size_t i = 0; i < pts.size(); ++i)
            {
                sf::Color c = (i == 0 || i == pts.size() - 1) ? sf::Color::Red : sf::Color::Magenta;
                bool isDragged = (draggedPointIndex == static_cast<int>(i));
                DrawControlPoint(window, *pts[i], c, 7.0f, isDragged);
            }
            };

        if (curveType == 0) // ЛИНЕЙНАЯ
        {
            Geometry::LinearBezierCurve<float> curve{ p0, p1 };
            if (showSkeleton) DrawLine(window, p0, p1, sf::Color(100, 100, 100));
            DrawBezierCurve(window, curve, segments, sf::Color::Cyan);

            if (showTangents)
            {
                Pointf pos = curve.PointAt(tangentParam);
                Vectorf dir = curve.Derivative() * tangentScale;
                DrawArrow(window, pos, dir, sf::Color::Yellow);
            }
            DrawPoints({ &p0, &p1 });
        }
        else if (curveType == 1) // КВАДРАТИЧНАЯ
        {
            Geometry::QuadraticBezierCurve<float> curve{ p0, p1, p2 };
            if (showSkeleton)
            {
                DrawLine(window, p0, p1, sf::Color(100, 100, 100));
                DrawLine(window, p1, p2, sf::Color(100, 100, 100));
            }
            DrawBezierCurve(window, curve, segments, sf::Color::Green);

            if (showTangents)
            {
                Pointf pos = curve.PointAt(tangentParam);
                Vectorf dir = curve.DerivativeAt(tangentParam) * tangentScale;
                DrawArrow(window, pos, dir, sf::Color::Yellow);
            }
            DrawPoints({ &p0, &p1, &p2 });
        }
        else if (curveType == 2) // КУБИЧЕСКАЯ
        {
            Geometry::CubicBezierCurve<float> curve{ p0, p1, p2, p3 };
            if (showSkeleton)
            {
                DrawLine(window, p0, p1, sf::Color(100, 100, 100));
                DrawLine(window, p1, p2, sf::Color(100, 100, 100));
                DrawLine(window, p2, p3, sf::Color(100, 100, 100));
            }
            DrawBezierCurve(window, curve, segments, sf::Color::Yellow);

            if (showTangents)
            {
                Pointf pos = curve.PointAt(tangentParam);
                Vectorf dir = curve.DerivativeAt(tangentParam) * tangentScale;
                DrawArrow(window, pos, dir, sf::Color::Cyan);
            }
            DrawPoints({ &p0, &p1, &p2, &p3 });
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}