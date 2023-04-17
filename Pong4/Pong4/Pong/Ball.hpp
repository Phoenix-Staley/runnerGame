#pragma once

#include <SFML/Graphics.hpp>

class Ball : public sf::CircleShape
{
public:
	Ball(float newRadius, const sf::Vector2f& newPos,
		const sf::Color& newColor) :
		sf::CircleShape(newRadius)
	{
		//this->setRadius(newRadius);
		this->setPosition(newPos);
		this->setFillColor(newColor);
	}

private:

};