#pragma once

#include <vector>
#include <memory>

#include <GeometryVisualizer/InputSystem/Interfaces/IInputHandler.h>

class InputDispatcher : public IInputHandler
{
private:
    std::vector<std::shared_ptr<IInputHandler>> m_handlers;

public:
    void AddHandler(std::shared_ptr<IInputHandler> handler)
    {
        if (handler) {
            m_handlers.push_back(handler);
        }
    }

    void PushFront(std::shared_ptr<IInputHandler> handler)
    {
        if (handler) {
            m_handlers.insert(m_handlers.begin(), handler);
        }
    }

    bool Handle(const sf::Event& event, const sf::RenderWindow& window) override
    {
        for (const auto& handler : m_handlers)
        {
            if (handler->Handle(event, window))
            {
                return true;
            }
        }

        return false;
    }
};