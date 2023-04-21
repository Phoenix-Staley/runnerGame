//   C:\Users\hundr\OneDrive\Documents\School Work\2023 SPRING\CPTS 122\Programming Assignments\runnerGame

#pragma once

#include <SFML/Graphics.hpp>

class Obstacle : public sf::Sprite {

protected:
	float speed;
	sf::Texture texture;


public:

	Obstacle() {
		speed = 0;
	}

	// constructor
	Obstacle(int width, const sf::Vector2f& nPos, sf::Texture & nText) {


		setTexture(nText);
		setScale(6, 6);
		setTextureRect(sf::IntRect(0, 0, 16 * width, 1600));
		//setScale(3, 10);

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