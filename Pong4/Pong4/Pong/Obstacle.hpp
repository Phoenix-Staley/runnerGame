//   C:\Users\hundr\OneDrive\Documents\School Work\2023 SPRING\CPTS 122\Programming Assignments\runnerGame

#pragma once

#include <SFML/Graphics.hpp>

class Obstacle : public sf::RectangleShape {

private:
	float speed;


public:

	// constructor
	Obstacle(int width, const sf::Vector2f& nPos, const sf::Color& nColor) {

		sf::Vector2f size(width, 2000);
		setSize(size);
		setFillColor(nColor);

		// position is at top left of geometry
		setPosition(nPos);

		speed = 0;
	}

	// sets speed
	void setSpeed(float s) {
		speed = s;
	}

	// gets speed
	float getSpeed() {
		return speed;
	}


};