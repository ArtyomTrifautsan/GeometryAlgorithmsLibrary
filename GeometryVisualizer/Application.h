#pragma once

#include <SFML/Graphics.hpp>

#include <GeometryVisualizer/InputSystem/InputManager.h>
#include <GeometryVisualizer/UI/ImGuiUI.h>
#include <GeometryVisualizer/Scene/SceneEditor.h>
#include <GeometryVisualizer/Scene/SceneRenderer.h>

class Application
{
private:
    sf::RenderWindow m_window;
    ImguiUI m_ui;
    SceneEditor m_editor;
    SceneRenderer m_sceneRenderer;
    InputManager m_inputManager;

    sf::Clock m_deltaClock;

public:
    Application() : 
        m_window(sf::VideoMode({ 1280, 720 }), "AiryEngine CAD"),
        m_editor(m_window)
    {
        m_window.setFramerateLimit(60);
        m_ui.Init(m_window);
        m_inputManager.AddHandler(m_editor.GetInputHandler());
    }

    ~Application() = default;

    void Run()
    {
        while (m_window.isOpen())
        {
            ProcessEvents();
            Update();
            Render();
        }
    }

private:
    void ProcessEvents()
    {
        while (const std::optional event = m_window.pollEvent())
        {
            m_ui.ProcessEvent(m_window, *event);

            if (event->is<sf::Event::Closed>()) 
            {
                m_window.close();
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea({ 0.f, 0.f },
                    { static_cast<float>(resized->size.x),
                     static_cast<float>(resized->size.y) });
                m_window.setView(sf::View(visibleArea));
            }

            m_inputManager.ProcessEvent(*event, m_window);
        }
    }

    void Update()
    {
        sf::Time deltaTime = m_deltaClock.restart();
        m_ui.Update(m_window, deltaTime);
        m_editor.Update();
    }

    void Render()
    {
        m_window.clear(sf::Color(35, 35, 35));
        m_window.resetGLStates();

        //m_window.setView(m_editor.GetCameraView());
        m_sceneRenderer.Render(m_editor.GetContext(), m_window);

        m_window.setView(m_window.getDefaultView());
        m_ui.Render(m_window, m_editor.GetContext());
        
        m_window.display();
    }
};