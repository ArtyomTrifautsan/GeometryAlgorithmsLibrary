#pragma once

#include <GeometryVisualizer/InputSystem/Interfaces/IInputHandler.h>
#include <GeometryVisualizer/Scene/Interfaces/IInteractable.h>
#include <GeometryVisualizer/Scene/SceneContext.h>


class SceneInteractionHandler : public IInputHandler
{
private:
    SceneContext& m_scene;
    bool m_isDragging = false;
    sf::Vector2f m_lastMouseWorldPos{ 0.0f, 0.0f };

public:
    explicit SceneInteractionHandler(SceneContext& scene)
        : m_scene(scene) {
    }

    bool Handle(const sf::Event& event, const sf::RenderWindow& window) override
    {
        if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
        {
            if (mousePressed->button == sf::Mouse::Button::Left)
            {
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePressed->position);

                m_scene.SelectObjectAt(worldPos.x, worldPos.y, 15.0f);
                ISceneObject* selected = m_scene.GetSelectedObject();

                m_isDragging = (selected != nullptr);

                if (m_isDragging)
                {
                    m_lastMouseWorldPos = worldPos;
                    return true;
                }
            }
        }

        else if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>())
        {
            if (m_isDragging)
            {
                if (auto* interactable = dynamic_cast<IInteractable*>(m_scene.GetSelectedObject()))
                {
                    sf::Vector2f currentWorldPos = window.mapPixelToCoords(mouseMoved->position);
                    sf::Vector2f delta = currentWorldPos - m_lastMouseWorldPos;

                    if (delta.x != 0.0f || delta.y != 0.0f)
                    {
                        interactable->Drag();
                        interactable->MoveTo(delta.x, delta.y);
                        m_lastMouseWorldPos = currentWorldPos;
                    }

                    return true;
                }
            }
        }

        else if (const auto* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>())
        {
            if (mouseReleased->button == sf::Mouse::Button::Left && m_isDragging)
            {
                m_isDragging = false;

                if (auto* interactable = dynamic_cast<IInteractable*>(m_scene.GetSelectedObject()))
                {
                    interactable->Select();
                }

                return true;
            }
        }

        return false;
    }
};