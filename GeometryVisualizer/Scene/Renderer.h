#pragma once
#include <SFML/Graphics.hpp>
#include "SceneContext.h"

class Renderer {
private:
    sf::RenderTarget& m_target;

public:
    explicit Renderer(sf::RenderTarget& target) : m_target(target) {}

    void DrawScene(const SceneContext& scene)
    {
        for (const auto& objPtr : scene.GetObjects()) {
            objPtr->Draw(m_target);
        }
    }
};