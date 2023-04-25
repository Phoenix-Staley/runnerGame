#pragma once

#include <SFML/Graphics.hpp>

#include "Obstacle.hpp"


class Hurdle : public Obstacle {

public:

	Hurdle(const sf::Vector2f& nPos, sf::Texture& nText)  : Obstacle() {

		

		setTexture(nText);
		setScale(6, 6);

		float height = getTextureRect().height * 6;
		sf::Vector2f np;
		np.x = nPos.x;
		np.y = nPos.y - height;

		setPosition(np);

		speed = 0;
	}

};