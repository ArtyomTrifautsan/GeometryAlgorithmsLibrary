#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include <imgui.h>

#include <GeometryVisualizer/InputSystem/Implements/InputDispatcher.h>
#include <GeometryVisualizer/InputSystem/Interfaces/IInputHandler.h>

class InputManager
{
private:
    InputDispatcher m_globalDispatcher;

public:
    void AddHandler(std::shared_ptr<IInputHandler> handler)
    {
        m_globalDispatcher.AddHandler(handler);
    }

    void ProcessEvent(const sf::Event& event, const sf::RenderWindow& window)
    {
        const ImGuiIO& io = ImGui::GetIO();

        bool isMouseEvent = event.is<sf::Event::MouseMoved>() ||
            event.is<sf::Event::MouseButtonPressed>() ||
            event.is<sf::Event::MouseButtonReleased>() ||
            event.is<sf::Event::MouseWheelScrolled>();

        bool isKeyEvent = event.is<sf::Event::KeyPressed>() ||
            event.is<sf::Event::KeyReleased>() ||
            event.is<sf::Event::TextEntered>();

        if (isMouseEvent && io.WantCaptureMouse) return;
        if (isKeyEvent && io.WantCaptureKeyboard) return;

        m_globalDispatcher.Handle(event, window);
    }
};