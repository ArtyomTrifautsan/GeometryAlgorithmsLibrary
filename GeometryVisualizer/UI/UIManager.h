#pragma once

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <cstdint>

#include <GeometryVisualizer/Scene/SceneContext.h>
#include <GeometryVisualizer/Scene/Implements/SceneObjects.h>

class UIManager
{
public:
    void Render(SceneContext& scene)
    {
        // 1. Отрисовываем верхнее меню окна (Main Menu Bar)
        RenderMainMenuBar(scene);

        // 2. Окно свойств выделенного объекта (Inspector)
        RenderPropertiesPanel(scene);
    }

private:
    // --- Верхняя панель меню ---
    void RenderMainMenuBar(SceneContext& scene)
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Create"))
            {
                if (ImGui::MenuItem("Linear Bezier Curve"))
                {
                    CreateLinearCurve(scene);
                }

                if (ImGui::MenuItem("Quadratic Bezier Curve"))
                {
                    CreateQuadraticCurve(scene);
                }

                if (ImGui::MenuItem("Cubic Bezier Curve"))
                {
                    CreateCubicCurve(scene);
                }

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    // --- Фабричные методы создания объектов ---

    void CreateLinearCurve(SceneContext& scene)
    {
        auto curve = std::make_unique<SceneLinearBezier2>();

        // Задаем стартовые координаты (например, по центру экрана)
        curve->SetControlPoint(0, { 300.0f, 350.0f });
        curve->SetControlPoint(1, { 600.0f, 350.0f });

        // Добавляем в сцену и сразу выделяем
        ISceneObject* rawPtr = curve.get();
        scene.AddObject(std::move(curve));
        scene.SelectObject(rawPtr);
    }

    void CreateQuadraticCurve(SceneContext& scene)
    {
        auto curve = std::make_unique<SceneQuadraticBezier2>();

        curve->SetControlPoint(0, { 300.0f, 450.0f });
        curve->SetControlPoint(1, { 450.0f, 200.0f });
        curve->SetControlPoint(2, { 600.0f, 450.0f });

        ISceneObject* rawPtr = curve.get();
        scene.AddObject(std::move(curve));
        scene.SelectObject(rawPtr);
    }

    void CreateCubicCurve(SceneContext& scene)
    {
        auto curve = std::make_unique<SceneCubicBezier2>();

        curve->SetControlPoint(0, { 300.0f, 450.0f });
        curve->SetControlPoint(1, { 400.0f, 200.0f });
        curve->SetControlPoint(2, { 500.0f, 200.0f });
        curve->SetControlPoint(3, { 600.0f, 450.0f });

        ISceneObject* rawPtr = curve.get();
        scene.AddObject(std::move(curve));
        scene.SelectObject(rawPtr);
    }

    // --- Панель инспектора свойств ---
    void RenderPropertiesPanel(SceneContext& scene)
    {
        ImGui::Begin("Inspector / Properties");

        ISceneObject* selected = scene.GetSelectedObject();

        if (!selected) {
            ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "No object selected.");
            ImGui::TextWrapped("Click on any curve in the scene or create one from the 'Create' menu above.");
            ImGui::End();
            return;
        }

        ImGui::Text("Type: %s", selected->Name().c_str());
        ImGui::Separator();

        // RTTI каст к соответствующим типам кривых
        if (auto cubic = dynamic_cast<SceneCubicBezier2*>(selected)) {
            DrawCurveProperties(cubic);
        }
        else if (auto quad = dynamic_cast<SceneQuadraticBezier2*>(selected)) {
            DrawCurveProperties(quad);
        }
        else if (auto linear = dynamic_cast<SceneLinearBezier2*>(selected)) {
            DrawCurveProperties(linear);
        }

        ImGui::End();
    }

    // --- Отображение свойств конкретной кривой ---
    template <typename TCore, GeometryType TType>
    void DrawCurveProperties(SceneBezierCurve<TCore, TType>* curve)
    {
        int segments = curve->GetSegments();
        if (ImGui::SliderInt("Segments", &segments, 2, 200)) {
            curve->SetSegments(segments);
        }

        ImGui::Spacing();

        bool showSkel = curve->GetShowSkeleton();
        if (ImGui::Checkbox("Show Skeleton", &showSkel)) {
            curve->SetShowSkeleton(showSkel);
        }

        bool showTang = curve->GetShowTangents();
        if (ImGui::Checkbox("Show Tangents", &showTang)) {
            curve->SetShowTangents(showTang);
        }

        ImGui::Spacing();

        if (showTang) {
            float tParam = curve->GetTangentParam();
            if (ImGui::SliderFloat("Tangent Param (t)", &tParam, 0.0f, 1.0f)) {
                curve->SetTangentParam(tParam);
            }

            float tScale = curve->GetTangentScale();
            if (ImGui::SliderFloat("Tangent Scale", &tScale, 0.01f, 2.0f)) {
                curve->SetTangentScale(tScale);
            }
            ImGui::Spacing();
        }

        // Цветовая палитра
        DrawColorEdit("Curve Color", curve,
            [](auto* c) { return c->GetCurveColor(); },
            [](auto* c, sf::Color col) { c->SetCurveColor(col); }
        );

        DrawColorEdit("Skeleton Color", curve,
            [](auto* c) { return c->GetSkeletonColor(); },
            [](auto* c, sf::Color col) { c->SetSkeletonColor(col); }
        );

        DrawColorEdit("Control Points Color", curve,
            [](auto* c) { return c->GetControlPointsColor(); },
            [](auto* c, sf::Color col) { c->SetControlPointsColor(col); }
        );

        DrawColorEdit("Tangent Color", curve,
            [](auto* c) { return c->GetTangentColor(); },
            [](auto* c, sf::Color col) { c->SetTangentColor(col); }
        );
    }

    template <typename TCurve, typename Getter, typename Setter>
    void DrawColorEdit(const char* label, TCurve* curve, Getter get, Setter set)
    {
        sf::Color sfColor = get(curve);

        float color[4] = {
            sfColor.r / 255.0f,
            sfColor.g / 255.0f,
            sfColor.b / 255.0f,
            sfColor.a / 255.0f
        };

        if (ImGui::ColorEdit4(label, color)) {
            set(curve, sf::Color(
                static_cast<std::uint8_t>(color[0] * 255.0f),
                static_cast<std::uint8_t>(color[1] * 255.0f),
                static_cast<std::uint8_t>(color[2] * 255.0f),
                static_cast<std::uint8_t>(color[3] * 255.0f)
            ));
        }
    }
};