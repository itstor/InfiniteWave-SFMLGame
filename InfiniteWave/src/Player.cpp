#include "Player.h"

#include <cmath>
#include <iostream>


Player::Player(): playerRect(entityRect)
{
	movementSpeed = 250.0f;
	ColliderBody.setSize(sf::Vector2f(50, 50));
	ColliderBody.setOrigin(25, 25);
}

void Player::Move(sf::Vector2i dir, float deltaTime)
{
	status = WALK_ANIM;
	if (dir.x < 0) //Left
	{
		movePos.x = -movementSpeed * deltaTime;
	}
	if (dir.x > 0) //Right
	{
		movePos.x = movementSpeed * deltaTime;
	}
	if (dir.y < 0) //Up
	{
		movePos.y = -movementSpeed * deltaTime;
	}
	if (dir.y > 0) //Down
	{
		movePos.y = movementSpeed * deltaTime;
	}
}

void Player::PlayerMove()
{
	entityRect.move(movePos);
	ColliderBody.move(movePos);
	movePos.x = 0.0f; movePos.y = 0.0f;
}


void Player::Update(float deltaTime)
{
	//Change animation based on status
	//TODO
	switch (status)
	{
	case IDLE_ANIM: break;
	case WALK_ANIM: break;
	case SHOOT_ANIM: break;
	default: break;
	}

	//Set back
	status = IDLE_ANIM;
}

void Player::lookAt(sf::Vector2f mousePos)
{
	const float PI = 3.14159265f;

	const sf::Vector2f dir(mousePos.x - playerRect.getPosition().x,
		mousePos.y - playerRect.getPosition().y);
	
	angle = (atan2(dir.y, dir.x)) * 180 / PI;

	dirVect = dir / sqrt(pow(dir.x, 2) + pow(dir.y, 2));

	playerRect.setRotation(angle);
}

sf::Vector2f Player::getPosition() const
{
	return playerRect.getPosition();
}

float Player::getAngle() const
{
	return angle;
}

sf::Vector2f Player::getDirVect() const
{
	return dirVect;
}
