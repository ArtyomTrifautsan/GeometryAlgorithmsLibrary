#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include <GeometryVisualizer/InputSystem/Implements/SceneInteractionHandler.h>
#include <GeometryVisualizer/InputSystem/Implements/InputDispatcher.h>
#include <GeometryVisualizer/Scene/SceneContext.h>

class SceneEditor
{
private:
    SceneContext m_context;
    sf::View m_cameraView;
    std::shared_ptr<InputDispatcher> m_sceneInputDispatcher;

public:
    explicit SceneEditor(const sf::RenderWindow& window)
    {
        m_cameraView = window.getDefaultView();
        m_sceneInputDispatcher = std::make_shared<InputDispatcher>();

        auto interactionHandler = std::make_shared<SceneInteractionHandler>(m_context);

        m_sceneInputDispatcher->AddHandler(interactionHandler);
    }

    void Update()
    {
        m_context.Update();
    }

    SceneContext& GetContext() { return m_context; }
    const SceneContext& GetContext() const { return m_context; }

    const sf::View& GetCameraView() const { return m_cameraView; }

    std::shared_ptr<IInputHandler> GetInputHandler() const
    {
        return m_sceneInputDispatcher;
    }
};