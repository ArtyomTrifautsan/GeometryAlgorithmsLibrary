#pragma once

#include <memory>
#include <cstdint>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

#include <GeometryVisualizer/Scene/SceneEditor.h>
#include <GeometryVisualizer/Scene/SceneContext.h>
#include <GeometryVisualizer/Scene/Implements/SceneObjects.h>

class UIManager : public ISceneObjectVisitor
{
public:
    void Render(SceneEditor& editor)
    {
        RenderMainMenuBar(editor);
        RenderPropertiesPanel(editor);
    }

    void Visit(SceneLinearBezier2& curve) override { DrawCurveProperties(&curve); }
    void Visit(SceneQuadraticBezier2& curve) override { DrawCurveProperties(&curve); }
    void Visit(SceneCubicBezier2& curve) override { DrawCurveProperties(&curve); }

private:
    void RenderMainMenuBar(SceneEditor& editor)
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Create"))
            {
                if (ImGui::MenuItem("Linear Bezier Curve"))
                {
                    editor.CreateAndSelectObject<SceneLinearBezier2>();
                }

                if (ImGui::MenuItem("Quadratic Bezier Curve"))
                {
                    editor.CreateAndSelectObject<SceneQuadraticBezier2>();
                }

                if (ImGui::MenuItem("Cubic Bezier Curve"))
                {
                    editor.CreateAndSelectObject<SceneCubicBezier2>();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void CreateLinearCurve(SceneContext& scene)
    {
        auto curve = std::make_unique<SceneLinearBezier2>();

        curve->SetControlPoint(0, { 300.0f, 350.0f });
        curve->SetControlPoint(1, { 600.0f, 350.0f });

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

    void RenderPropertiesPanel(SceneEditor& editor)
    {
        ImGui::Begin("Inspector / Properties");

        ISceneObject* selected = editor.GetContext().GetSelectedObject();

        if (!selected) {
            ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "No object selected.");
            ImGui::TextWrapped("Click on any curve in the scene or create one from the 'Create' menu above.");
            ImGui::End();
            return;
        }

        ImGui::Text("Type: %s", selected->Name().c_str());
        ImGui::Separator();

        selected->Accept(*this);

        ImGui::End();
    }

    template <typename TCore>
    void DrawCurveProperties(SceneBezierCurve<TCore>* curve)
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

        if (showTang)
        {
            float tParam = curve->GetTangentParam();
            if (ImGui::SliderFloat("Tangent parametr (t)", &tParam, 0.0f, 1.0f)) {
                curve->SetTangentParam(tParam);
            }

            float tScale = curve->GetTangentScale();
            if (ImGui::SliderFloat("Tangent scale", &tScale, 0.01f, 2.0f)) {
                curve->SetTangentScale(tScale);
            }
            ImGui::Spacing();
        }

        DrawColorEdit("Curve color", curve,
            [](auto* c) { return c->GetCurveColor(); },
            [](auto* c, sf::Color col) { c->SetCurveColor(col); }
        );

        if (showSkel)
        {
            DrawColorEdit("Skeleton color", curve,
                [](auto* c) { return c->GetSkeletonColor(); },
                [](auto* c, sf::Color col) { c->SetSkeletonColor(col); }
            );

            DrawColorEdit("Control points color", curve,
                [](auto* c) { return c->GetControlPointsColor(); },
                [](auto* c, sf::Color col) { c->SetControlPointsColor(col); }
            );
        }

        if (showTang)
        {
            DrawColorEdit("Tangent color", curve,
                [](auto* c) { return c->GetTangentColor(); },
                [](auto* c, sf::Color col) { c->SetTangentColor(col); }
            );
        }
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