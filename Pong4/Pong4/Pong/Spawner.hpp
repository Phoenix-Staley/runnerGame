#pragma once

#include<vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>

#include "Obstacle.hpp"
#include "Hurdle.hpp"
#include "Grass.hpp"
#include "Cloud.hpp"

class Spawner {
	public:
		Spawner(int currHeight, int timeToObstacle, const int unitSize, sf::Texture* textures, std::vector<Obstacle*>* objectVect, double* currSpeed);
		~Spawner() {}

		int getHeight(void) { return this->currHeight; }
		void setHeight(int newHeight) { this->currHeight = newHeight; }
		int getTimeToObstacle(void) { return this->currHeight; }
		void setTimeToObstacle(int newTime) { this->timeToObstacle = newTime; }
		int getSpeed(void) { return *(this->currSpeed); }
		void setSpeed(int newSpeed) { *(this->currSpeed) = newSpeed; }
		std::vector<Obstacle*>& getObjVect(void) { return *(this->objectVect); }

		void cleanOutObstacles(void);

		void spawnNewGround(void);

		void spawnStartingGround(void);

		void adjustHeight(void);

		void chooseNextObstacle(bool& isAGap, const int xPos, const int yPos);

	protected:
		int currHeight; // 0-10 with 0 being the top of the screen
		int timeToObstacle;
		int unitSize;
		double speedIncrease; // This is only changed once, so the speed doesn't grow exponentially
		double* currSpeed;
		sf::Texture* textures; // [ ground, tall obstacle, short obstacle, grass ]
		std::vector<Obstacle*>* objectVect;
};