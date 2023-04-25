#pragma once

#include<vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>

#include "Obstacle.hpp"
#include "Hurdle.hpp"
#include "Grass.hpp"

class Spawner {
	public:
		Spawner(int currHeight, int timeToObstacle, const int unitSize, sf::Texture* textures, std::vector<Obstacle*>* objectVect, double* currSpeed);
		~Spawner() {}

		void cleanOutObstacles(void);

		void spawnNewGround(void);

		void spawnStartingGround(void);

	protected:
		int currHeight;
		int timeToObstacle;
		int unitSize;
		double* currSpeed;
		sf::Texture* textures; // [ ground, tall obstacle, short obstacle, grass ]
		std::vector<Obstacle*>* objectVect;
};