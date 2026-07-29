#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

#include "UIManager.h" // Ваш класс с логикой отрисовки панелей свойств

class ImGuiUI
{
public:
    ImGuiUI() = default;
    ~ImGuiUI() { Shutdown(); }

    // Инициализация ImGui (вызывать один раз после создания окна)
    bool Init(sf::RenderWindow& window)
    {
        return ImGui::SFML::Init(window);
    }

    // Обработка событий (вызывать внутри цикла while(window.pollEvent(event)))
    void ProcessEvent(sf::RenderWindow& window, const sf::Event& event)
    {
        ImGui::SFML::ProcessEvent(window, event);
    }

    // Подготовка нового кадра (вызывать каждый кадр перед отрисовкой)
    void Update(sf::RenderWindow& window, sf::Time dt)
    {
        ImGui::SFML::Update(window, dt);
    }

    // Отрисовка интерфейса (вызывать между window.clear() и window.display())
    void Render(sf::RenderWindow& window, SceneContext& scene)
    {
        // 1. Формируем логику наших окон (свойства выделенного объекта)
        m_uiManager.Render(scene);

        // 2. Отрисовываем буфер ImGui поверх окна SFML
        ImGui::SFML::Render(window);
    }

    // Очистка ресурсов
    void Shutdown()
    {
        ImGui::SFML::Shutdown();
    }

    // Очень важный метод! Защищает от кликов "сквозь" интерфейс
    [[nodiscard]] bool WantCaptureMouse() const
    {
        return ImGui::GetIO().WantCaptureMouse;
    }

private:
    UIManager m_uiManager;
};