// This example will use SFML libraries to implement
// the game of Pong

// History:  - Started from the SFML tutorial code that draws
//                a circle in the window.
//
//          4/12/23 - declared two Paddle objects. added detection for 
//                    key presses to move the paddles
//                    down, but no up yet. added collision detection
//                    between p2Paddle and the gameBall.
// 
//          4/10/23 - completed the Paddle class.
// 
//          4/7/23 - declared a Ball class and started working on a Paddle
//                   class. discussed some of the fundamental game
//                   design structures: the event queue, event-driven
//                   programming, polling for events, etc.

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Ball.hpp"
#include "Paddle.hpp"



int main()
{
	std::vector<int> v1 = {1,8,4,2,9};
	std::vector<int>::iterator it;

	int n1 = v1.at(2);

	for (it = v1.begin(); it < v1.end(); it++)
	{
		std::cout << "v1: " << *it << std::endl;
		//v1.at(it);
	}

	// range based for loop
	for (auto i : v1 )
	{
		std::cout << "i: " << i << std::endl;
	}

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	window.setFramerateLimit(50);
//	sf::CircleShape shape(100.f);

	Ball gameBall(30.f, sf::Vector2f(500, 500), sf::Color::White);
	Paddle p1Paddle(sf::Vector2f(gameBall.getRadius()/3, 
		gameBall.getRadius()*4), sf::Vector2f(0, 0), sf::Color::Red),
		p2Paddle(sf::Vector2f(gameBall.getRadius() / 3,
			gameBall.getRadius() * 4), 
			sf::Vector2f(window.getSize().x - p1Paddle.getSize().x, 0), 
			sf::Color::Red);

	int direction = 1;
//	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			p1Paddle.move(0, 5);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			p2Paddle.move(0, 5);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			p1Paddle.move(0, -5);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			p2Paddle.move(0, -5);
		}

		// is there a collision between the paddle and ball?
		if (p2Paddle.getGlobalBounds().intersects(gameBall.getGlobalBounds()))
		{
			direction *= -1; // change the direction of the ball
		}

		if (p1Paddle.getGlobalBounds().intersects(gameBall.getGlobalBounds()))
		{
			direction *= -1; // change the direction of the ball
		}

		gameBall.move(3 * direction, 0);

		window.clear();
		window.draw(p1Paddle);
		window.draw(p2Paddle);
		window.draw(gameBall);
		window.display();
	}

	return 0;
}