#include<iostream>

#include "Spawner.hpp"

Spawner::Spawner(int currHeight, int timeToObstacle, const int unitSize, sf::Texture* textures, std::vector<Obstacle*>* objectVect, double *currSpeed) {
	this->currSpeed = currSpeed;
	this->speedIncrease = *currSpeed / 30;
	*(this->currSpeed) += this->speedIncrease;
	this->objectVect = objectVect;
	this->currHeight = currHeight;
	this->timeToObstacle = timeToObstacle;
	this->unitSize = unitSize;
	this->textures = textures;
}

void Spawner::cleanOutObstacles(void) {
	for (auto& i : *(this->objectVect)) {
		// If any given object is off the screen, remove it from the object vector
		if (i->getPosition().x < -(this->unitSize * 3)) {
			this->objectVect->erase(std::remove(this->objectVect->begin(), this->objectVect->end(), i));
		}
	}
}

void Spawner::spawnNewGround(void) {
	// Do not generate anything when the game ends
	if (*(this->currSpeed) == 0) { return; }

	// Spawns the ground to the right of the screen
	const int xPos = 1000 + this->unitSize;
	const int yPos = this->unitSize * this->currHeight;

	// If switched to true in obstacle generation, the next section of ground will not generate
	bool isAGap = false;

	this->adjustHeight();

	if (this->timeToObstacle == 0) {
		this->chooseNextObstacle(isAGap, xPos, yPos);
	}

	if (!isAGap) {
		// yPos + 1 ensures the grass is always above the ground
		// this way, the player only collides with the grass
		Obstacle* ground = new Obstacle(3, sf::Vector2f(xPos, yPos + 12), this->textures[0]);
		Obstacle* grass = new Grass(3, sf::Vector2f(xPos, yPos), this->textures[3]);

		this->objectVect->push_back(ground);
		this->objectVect->push_back(grass);
	}

	if (rand() % 10 == 1) {
		Obstacle* cloud = new Cloud(sf::Vector2f(xPos, this->unitSize * ((rand() % 3) + 0.5)), this->textures[4]);

		this->objectVect->push_back(cloud);
	}

	this->timeToObstacle--;

	if (*(this->currSpeed) < 5 * (*(this->currSpeed))) {
		*(this->currSpeed) += this->speedIncrease;
	}
}

// Spawn the initial ground, before hurdles start spawning
void Spawner::spawnStartingGround(void) {
	const int yPos = this->unitSize * this->currHeight;

	for (int xPos = 0; xPos < 1000; xPos += (unitSize * 3)) {
		Obstacle* groundTile = new Obstacle(3, sf::Vector2f(xPos, yPos + 12), this->textures[0]);
		Obstacle* grassTile = new Grass(3, sf::Vector2f(xPos, yPos), this->textures[3]);

		this->objectVect->push_back(groundTile);
		this->objectVect->push_back(grassTile);
	}
}

// 20% chance to adjust the height up or down
void Spawner::adjustHeight(void) {
	// This does not adjust the height on the same loop a hurdle is placed
	if (this->timeToObstacle > 2 && (rand() % 10) > 7) {
		// The ++ and -- seem swapped, but this is because y = 0 is at the top of the screen
		// So, increasing currHeight lowers the ground, and vice versa
		if (this->currHeight == 5) {
			// If this is at it's max height, lower it down
			this->currHeight++;
		}
		else if (this->currHeight == 9) {
			// If this is at it's minimum height, raise it up
			this->currHeight--;
		}
		else {
			// Randomly add 1 or -1 to the height
			this->currHeight += (rand() % 2) ? -1 : 1;
		}
	}
}

// Randomly chooses to spawn a tall tree, short tree, or a gap
void Spawner::chooseNextObstacle(bool& isAGap, const int xPos, const int yPos) {
		int obstacleType = rand() % 3;

		if (obstacleType == 2) {
			Obstacle* highHurdle = new Hurdle(sf::Vector2f(xPos, yPos), this->textures[1]);
			this->objectVect->push_back(highHurdle);
		}
		else if (obstacleType == 1) {
			// The +182 ensures the short hurdle is in-line with the ground
			Obstacle* shortHurdle = new Hurdle(sf::Vector2f(xPos + 182, yPos), this->textures[2]);
			this->objectVect->push_back(shortHurdle);
		}
		else {
			// Lets the parent function know to not generate terrain
			isAGap = true;
		}

		// Between 2 and 5 generations, AKA 6-15 units
		this->timeToObstacle = (rand() % 4) + 3;
}