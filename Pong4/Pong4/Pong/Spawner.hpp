#pragma once

#include<vector>
#include <algorithm>

#include "Obstacle.hpp"
#include "Hurdle.hpp"

class Spawner {
	public:
		Spawner(void) {}
		~Spawner() {}
};

void cleanOutVector(std::vector<Obstacle*>& objectVect, const int unitSize);

void spawnNewGround(int& generation, std::vector<Obstacle*> &objectVect, sf::Texture textures[3], const int unitSize);

void spawnStartingGround(std::vector<Obstacle*>& objectVect, sf::Texture &groundTexture, const int unitSize);