// **this is testing only don't use this for the actual player**

#pragma once

#include <SFML/Graphics.hpp>

class Animation : public sf::Sprite {

private:
	sf::Texture sprites[7];
	//sf::Texture jumpSprite;
	int animationCount = 0;
	int frameCount = 0;
	int frameRate = 10;


	void updateSprite() {

		animationCount--;
		if (animationCount < 0)
			animationCount = 5;

		setTexture(sprites[animationCount]);
	}

	void jumpSprite() {
		setTexture(sprites[6]);
	}

public:

	Animation(const sf::Vector2f& nPos, int nFrameRate) {

		sprites[0].loadFromFile("player_sprites/run6.png");
		sprites[1].loadFromFile("player_sprites/run5.png");
		sprites[2].loadFromFile("player_sprites/run4.png");
		sprites[3].loadFromFile("player_sprites/run3.png");
		sprites[4].loadFromFile("player_sprites/run2.png");
		sprites[5].loadFromFile("player_sprites/run1.png");

		sprites[6].loadFromFile("player_sprites/jump.png");

		setScale(6, 6);
		animationCount = 0;
		frameRate = nFrameRate;
		frameCount = frameRate;

		setTexture(sprites[0]);
		setPosition(nPos);
	}

	void frameUpdate(double jumpSpeed) {

		frameCount--;
		if (jumpSpeed == 0) {
			if (frameCount < 0) {
				frameCount = frameRate;
				updateSprite();
			}
		}
		else {
			jumpSprite();
		}
	}

};