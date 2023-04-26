#include "Player.hpp"

// returns whether the player can keep increasing in jump height or not. Once false, the player will begin falling
bool Player::jumpActive()
{
	if (this->jumpTime > this->maxJumpTime) // only lets the player jump to a certain height
	{
		return false;
	}
	return true;
}

// gets called every frame. Jumps if pressing space, and falls if not.
void Player::updateMovement(bool isTouchingGround)
{
	if (jumpActive() && (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) // jump if conditions are met
	{
		this->move(0, jumpSpeed);
		fallVelocity = jumpSpeed; // preps the velocity for when the player begins falling
		jumpTime++;
	}
	else if (!isTouchingGround && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // crouch if conditions are met
	{
		fallVelocity = maxFallVelocity;
		this->move(0, fallVelocity);
	}
	else
	{
		if (!isTouchingGround) // only enabled when midair
		{
			jumpTime = maxJumpTime + 1;
			fallVelocity += fallSpeed;
			this->move(0, fallVelocity);
			if (fallVelocity > maxFallVelocity) // max fall velocity such that player does not clip through the grass
			{
				fallVelocity = maxFallVelocity;
			}
		}
		else // reset fall velocity and jumpTime tracking once player is on the ground again
		{
			this->jumpTime = 0;
			fallVelocity = 0;
		}
	}
}

double Player::getVelocity() {
	return fallVelocity;
}