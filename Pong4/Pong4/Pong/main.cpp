#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>

#include "Obstacle.hpp"
#include "Player.hpp"

using std::vector;

int main()
{
	// the speed at which obstacles should move
	float curSpeed = 1;
	bool touchingGround = false;

	// self explanatory
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "runner game");
	window.setFramerateLimit(100);

	// creates the collection of obstacles
	vector<Obstacle*> obVect; // we need to have pointers, copies don't work I tried

	// objects for testing
	Obstacle o1(100, sf::Vector2f(500, 500), sf::Color::Red);
	Obstacle o2(100, sf::Vector2f(600, 600), sf::Color::Red);
	Obstacle o3(100, sf::Vector2f(700, 700), sf::Color::Red);

	// Player object
	Player player(sf::Vector2f(100, 100), sf::Vector2f(500, 200));

	// push_back is the same as inserting, the insert() function doens't work like you'd think
	obVect.push_back(&o1);
	obVect.push_back(&o2);
	obVect.push_back(&o3);


	while (window.isOpen())
	{
		touchingGround = false;

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