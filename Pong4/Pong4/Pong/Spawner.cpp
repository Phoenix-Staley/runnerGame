#include<iostream>

#include "Spawner.hpp"

void cleanOutVector(std::vector<Obstacle*>& objectVect, const int unitSize) {
	for (auto& i : objectVect) {
		if (i->getPosition().x < -unitSize) {
			objectVect.erase(std::remove(objectVect.begin(), objectVect.end(), i));
		}
	}
}

void spawnNewGround(int& generation, std::vector<Obstacle*> &objectVect, sf::Texture textures[3], const int unitSize) {
	const int xPos = 1000 + unitSize;
	const int yPos = unitSize * 5;

	generation = unitSize * 3; // 3 is the amount of blocks
	Obstacle* oT = new Obstacle(3, sf::Vector2f(xPos, yPos), textures[0]);

	// polymorphism baby!
	Obstacle* hT = new Hurdle(sf::Vector2f(xPos, yPos), textures[1]);
	Obstacle* sT = new Hurdle(sf::Vector2f(xPos + 182, yPos), textures[2]);

	objectVect.push_back(oT);
	objectVect.push_back(sT);
	objectVect.push_back(hT);

	cleanOutVector(objectVect, unitSize);
}

void spawnStartingGround(std::vector<Obstacle*>& objectVect, sf::Texture &groundTexture, const int unitSize) {
	const int yPos = unitSize * 6;

	for (int xPos = 0; xPos < 1000; xPos += unitSize) {
		Obstacle* groundTile = new Obstacle(3, sf::Vector2f(xPos, yPos), groundTexture);

		objectVect.push_back(groundTile);
	}
}