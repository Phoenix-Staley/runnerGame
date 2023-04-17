#pragma once

#include <SFML/Graphics.hpp>

class Paddle : public sf::RectangleShape
{
public:
	Paddle (sf::Vector2f &newSize, const sf::Vector2f& newPos,
		const sf::Color& newColor) : 
		sf::RectangleShape(newSize)
	{
		this->setFillColor(newColor);
		this->setPosition(newPos);
	}
	
};
