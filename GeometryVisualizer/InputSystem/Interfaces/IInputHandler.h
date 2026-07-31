#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class IInputHandler
{
public:
	virtual ~IInputHandler() = default;

	virtual bool Handle(const sf::Event& event, const sf::RenderWindow& window) = 0;
};