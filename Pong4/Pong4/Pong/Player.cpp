#include "Player.hpp"

// returns whether the player can keep increasing in jump height or not. Once false, the player will begin falling
bool Player::jumpActive()
{
	if (this->jumpTime == NULL)
	{
		this->jumpTime = clock();
	}
	else if (this->jumpTime > this->maxJumpTime)
	{
		return false;
	}

	return true;
}

// gets called every frame. Jumps if pressing space, and falls if not.
void Player::updateMovement()
{
	if (jumpActive() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->move(0, jumpSpeed);
		fallVelocity = jumpSpeed;
	}
	else
	{
		fallVelocity += 0.25;
		this->move(0, fallVelocity);
	}
}