#pragma once

#include <SFML/Graphics.hpp>

#include "Obstacle.hpp"


class Grass : public Obstacle {

public: 
	Grass(int width, const sf::Vector2f& nPos, sf::Texture& nText) : Obstacle() {

		setTexture(nText);

		setScale(6, 6);
		setTextureRect(sf::IntRect(0, 0, 16 * width, 16));

		setPosition(nPos);

		speed = 0;
	}

};