#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include <GeometryVisualizer/Scene/SceneContext.h>
#include <GeometryVisualizer/Scene/Implements/SceneObjects.h>
#include <GeometryVisualizer/UI/ImGuiUI.h>

int main()
{
    // 1. В SFML 3.0 VideoMode принимает sf::Vector2u в фигурных скобках
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Geometry Engine - Bezier Curves");
    window.setFramerateLimit(60);

    SceneContext scene;

    scene.AddObject(std::make_unique<SceneCubicBezier2>());

    scene.AddObject(std::make_unique<SceneQuadraticBezier2>());

    ImGuiUI ui;
    if (!ui.Init(window))
    {
        return -1;
    }

    sf::Clock deltaClock;

    bool isDragging = false;
    sf::Vector2f lastMouseWorldPos{ 0.0f, 0.0f };

    while (window.isOpen())
    {
        // --- Внутри цикла while (window.pollEvent()) ---
        while (const std::optional event = window.pollEvent())
        {
            // Обязательно передаем события в ImGui
            ImGui::SFML::ProcessEvent(window, *event);

            // 1. НАЖАТИЕ МЫШИ
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (!ui.WantCaptureMouse() && mousePressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f worldPos = window.mapPixelToCoords(mousePressed->position);

                    // Одна строчка: находит верхний объект, меняет состояния, а при клике в пустоту сбрасывает выбор
                    scene.SelectObjectAt(worldPos.x, worldPos.y, 15.0f);

                    ISceneObject* selected = scene.GetSelectedObject();
                    isDragging = (selected != nullptr);

                    if (isDragging)
                    {
                        lastMouseWorldPos = worldPos;
                    }
                }
            }

            // 2. ПЕРЕМЕЩЕНИЕ МЫШИ
            else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                if (isDragging)
                {
                    if (auto* interactable = dynamic_cast<IInteractable*>(scene.GetSelectedObject()))
                    {
                        sf::Vector2f currentWorldPos = window.mapPixelToCoords(mouseMoved->position);
                        sf::Vector2f delta = currentWorldPos - lastMouseWorldPos;

                        if (delta.x != 0.0f || delta.y != 0.0f)
                        {
                            interactable->Drag();
                            interactable->MoveTo(delta.x, delta.y);
                            lastMouseWorldPos = currentWorldPos;
                        }
                    }
                }
            }

            // 3. ОТПУСКАНИЕ МЫШИ
            else if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (mouseReleased->button == sf::Mouse::Button::Left && isDragging)
                {
                    isDragging = false;

                    if (auto* interactable = dynamic_cast<IInteractable*>(scene.GetSelectedObject()))
                    {
                        // Переводим из Dragged обратно в Selected
                        interactable->Select();
                    }
                }
            }
        }

        sf::Time dt = deltaClock.restart();

        ui.Update(window, dt);
        scene.Update();

        window.clear(sf::Color(30, 30, 30));

        scene.Draw(window);
        ui.Render(window, scene);

        window.display();
    }

    return 0;
}