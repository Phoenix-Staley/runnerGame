#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>

#include "Obstacle.hpp"
#include "Player.hpp"
#include "Hurdle.hpp"
#include "Animation.hpp"
#include "Grass.hpp"

using std::vector;

int main()
{
	// pixels per unit
	int UNITSIZE = 96;

	/// dirt texture
	sf::Texture blockTexture;	
	blockTexture.loadFromFile("testDirt.png");
	blockTexture.setRepeated(true);

	/// grass texture
	sf::Texture grassTexture;
	grassTexture.loadFromFile("testGrass.png");
	grassTexture.setRepeated(true);
	
	/// tree texture
	sf::Texture treeTexture;	
	treeTexture.loadFromFile("testTree.png");
	//treeTexture.setRepeated(true);

	/// shrub texture
	sf::Texture shrubTexture;
	shrubTexture.loadFromFile("testShrub.png");

	// the speed at which obstacles should move
	float curSpeed = 1;
	bool touchingGround = false;

	// self explanatory
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "runner game");
	window.setFramerateLimit(100);

	// creates the collection of obstacles
	vector<Obstacle*> obVect; // we need to have pointers, copies don't work I tried

	// objects for testing
	Obstacle o1(1, sf::Vector2f(500-(96*2), 500), blockTexture);
	Obstacle o2(1, sf::Vector2f(596 - (96 * 2), 600), blockTexture);
	Obstacle o3(1, sf::Vector2f(692 - (96 * 2), 700), blockTexture);

	// Player object
	Player player(sf::Vector2f(100, 100), sf::Vector2f(500, 200));

	// push_back is the same as inserting, the insert() function doens't work like you'd think
	obVect.push_back(&o1);
	obVect.push_back(&o2);
	obVect.push_back(&o3);

	// 96 is pixels per unit/block
	int generationCounter = UNITSIZE * 3;


	/// player animation test
	Animation player(sf::Vector2f(500, 404), 10);


	while (window.isOpen())
	{
		touchingGround = false;
		generationCounter--;
		if (generationCounter == 0) {
			generationCounter = UNITSIZE * 3; // 3 is the amount of blocks
			Obstacle* oT = new Obstacle(3, sf::Vector2f(700, 500), blockTexture);

			// polymorphism baby!
			Obstacle* hT = new Hurdle(sf::Vector2f(700, 500), treeTexture);
			Obstacle* sT = new Hurdle(sf::Vector2f(882, 500), shrubTexture);

			// grass
			Obstacle* gT = new Grass(3, sf::Vector2f(700, 500), grassTexture);

			obVect.push_back(oT);
			obVect.push_back(sT);
			obVect.push_back(hT);
			obVect.push_back(gT);
		}


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// set each obstacles speed
		for (auto i : obVect) {
			i->setSpeed(curSpeed);
		}

		// move each obstacle
		for (auto i : obVect) {
			i->move(-i->getSpeed(), 0);
		}

		// check if player collides with any obstacle
		for (auto i : obVect) {
			if (player.getGlobalBounds().intersects(i->getGlobalBounds()))
			{
				touchingGround = true;
			}
		}

		// update player location
		player.updateMovement(touchingGround);


		/// update animation fram
		player.frameUpdate();

		// clear the window before drawing shit
		window.clear();

		

		// draw each obstacle
		for (auto i : obVect) {
			window.draw(*i);
		}

		// draw player
		window.draw(player);

		window.display();
	}

	return 0;
}