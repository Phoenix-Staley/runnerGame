#include<iostream>

#include "Spawner.hpp"

Spawner::Spawner(int currHeight, int timeToObstacle, const int unitSize, sf::Texture* textures, std::vector<Obstacle*>* objectVect, double *currSpeed) {
	this->currSpeed = currSpeed;
	this->objectVect = objectVect;
	this->currHeight = currHeight;
	this->timeToObstacle = timeToObstacle;
	this->unitSize = unitSize;
	this->textures = textures;
}

void Spawner::cleanOutObstacles(void) {
	for (auto& i : *(this->objectVect)) {
		if (i->getPosition().x < -(this->unitSize * 2)) {
			this->objectVect->erase(std::remove(this->objectVect->begin(), this->objectVect->end(), i));
		}
	}
}

void Spawner::spawnNewGround(void) {
	const int xPos = 1000 + this->unitSize;
	const int yPos = this->unitSize * this->currHeight;
	bool isGap = false;

	if (this->timeToObstacle != 1 && (rand() % 10) > 7) {
		if (this->currHeight == 3) {
			this->currHeight++;
		}
		else if (this->currHeight == 10) {
			this->currHeight--;
		}
		else {
			// Add -1, 0, or 1
			this->currHeight += (rand() % 2) ? -1 : 1;
		}
	}

	if (this->timeToObstacle == 0) {
		int obstacleType = rand() % 3;

		if (obstacleType == 2) {
			Obstacle* highHurdle = new Hurdle(sf::Vector2f(xPos, yPos), this->textures[1]);
			this->objectVect->push_back(highHurdle);
		}
		else if (obstacleType == 1) {
			Obstacle* shortHurdle = new Hurdle(sf::Vector2f(xPos + 182, yPos), this->textures[2]);
			this->objectVect->push_back(shortHurdle);
		}
		else {
			isGap = true;
		}

		// Between 2 and 5 generations, AKA 6-15 units
		this->timeToObstacle = (rand() % 4) + 2;
	}

	if (!isGap) {
		// yPos - 1 ensures the grass is always above the ground
		// this way, the player only collides with the grass
		Obstacle* ground = new Obstacle(3, sf::Vector2f(xPos, yPos + 1), this->textures[0]);
		Obstacle* grass = new Grass(3, sf::Vector2f(xPos, yPos), this->textures[3]);

		this->objectVect->push_back(ground);
		this->objectVect->push_back(grass);
	}

	this->timeToObstacle--;
	*(this->currSpeed) *= 1.01;
}

void Spawner::spawnStartingGround(void) {
	const int yPos = this->unitSize * this->currHeight;

	for (int xPos = 0; xPos < 1000; xPos += unitSize) {
		Obstacle* groundTile = new Obstacle(3, sf::Vector2f(xPos, yPos), this->textures[0]);
		Obstacle* grassTile = new Grass(3, sf::Vector2f(xPos, yPos), this->textures[3]);

		this->objectVect->push_back(groundTile);
		this->objectVect->push_back(grassTile);
	}
}