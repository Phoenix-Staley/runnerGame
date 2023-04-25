#pragma once

#include <SFML/Graphics.hpp>

#include "Obstacle.hpp"


class Cloud : public Obstacle {

public:
	Cloud(const sf::Vector2f& nPos, sf::Texture& nText) : Obstacle() {

		setTexture(nText);

		setScale(6, 6);

		setPosition(nPos);

		speed = 0;
	}

	void frameUpdate(int nSpeed) {

		setSpeed((nSpeed * 0.5));
		move(-speed, 0);
	}

};