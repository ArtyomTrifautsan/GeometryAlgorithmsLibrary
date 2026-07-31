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

    template <typename ObjType, typename... Args>
    ObjType* CreateAndSelectObject(Args&&... args)
    {
        std::unique_ptr<ObjType> obj = std::make_unique<ObjType>(std::forward<Args>(args)...);
        ObjType* rawObj = obj.get();

        m_context.AddObject(std::move(obj));
        m_context.SelectObject(rawObj);

        return rawObj;
    }

    SceneContext& GetContext() { return m_context; }
    const SceneContext& GetContext() const { return m_context; }

    const sf::View& GetCameraView() const { return m_cameraView; }

    std::shared_ptr<IInputHandler> GetInputHandler() const
    {
        return m_sceneInputDispatcher;
    }
};