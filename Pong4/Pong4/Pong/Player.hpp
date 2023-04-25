#pragma once

//#include <cstudio>
#include "SFML/Graphics.hpp"
#include <iostream>
#include <ctime>

class Player : public sf::RectangleShape
{
public:
	Player(sf::Vector2f& newSize, const sf::Vector2f& newPos)
	{
		this->setFillColor(sf::Color::White);
		this->setSize(newSize);
		this->setPosition(newPos);
	};

	bool jumpActive(bool isTouchingGround);
	void updateMovement(bool isTouchingGround);
private:
	double fallVelocity = 0;
	const double jumpSpeed = -10;
	clock_t jumpTime = NULL;
	const int maxJumpTime = 20;
};