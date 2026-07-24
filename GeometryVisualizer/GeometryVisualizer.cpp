#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "ImGui Test");
    window.setFramerateLimit(60);

    // Инициализируем ImGui для нашего окна
    if (!ImGui::SFML::Init(window))
    {
        return -1;
    }

    sf::Clock deltaClock;

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // Обновляем состояние ImGui
        ImGui::SFML::Update(window, deltaClock.restart());

        // Создаем тестовое окно ImGui
        ImGui::Begin("Hello, Geometry!");
        ImGui::Text("ImGui + SFML 3.0 successfully configured!");
        ImGui::End();

        window.clear(sf::Color(40, 40, 40));

        // Отрисовываем интерфейс ImGui
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}