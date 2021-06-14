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
		velocity.x = -movementSpeed * deltaTime;
	}
	if (dir.x > 0) //Right
	{
		velocity.x = movementSpeed * deltaTime;
	}
	if (dir.y < 0) //Up
	{
		velocity.y = -movementSpeed * deltaTime;
	}
	if (dir.y > 0) //Down
	{
		velocity.y = movementSpeed * deltaTime;
	}
}

void Player::PlayerMove()
{
	entityRect.move(velocity);
	ColliderBody.move(velocity);
	velocity.x = 0.0f; velocity.y = 0.0f;
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

	const float dx = mousePos.x - playerRect.getPosition().x;
	const float dy = mousePos.y - playerRect.getPosition().y;

	const float rotation = (atan2(dy, dx)) * 180 / PI;

	angle = rotation;

	playerRect.setRotation(rotation);
}

sf::Vector2f Player::getPosition() const
{
	return position;
}