#include "Player.h"

#include <cmath>
#include <iostream>
#include <SFML/Window/Mouse.hpp>


Player::Player(): playerRect(entityRect)
{
	//setup player
	movementSpeed = 150.0f;
	
	ColliderBody.setSize(sf::Vector2f(253, 216));
	ColliderBody.setOrigin(105, 120);
	playerRect.setSize(sf::Vector2f(253, 216));
	playerRect.setOrigin(105, 120);
	playerFeetRect.setSize(sf::Vector2f(172, 124));
	playerFeetRect.setOrigin(86, 62);
	//playerRect.setFillColor(sf::Color::Red);

	//init animation texture
	bodyTex.loadFromFile("Assets/Texture/Sprites/Player/playerspites.png");
	bodyTex.setSmooth(true);
	playerRect.setTexture(&bodyTex);

	feetTex.loadFromFile("Assets/Texture/Sprites/Player/feetplayer.png");
	feetTex.setSmooth(true);
	playerFeetRect.setTexture(&feetTex);
	

	//init animation
	bodyAnim.Setup(&bodyTex, 3, 20);
	feetAnim.Setup(&feetTex, 1, 21);
}

void Player::Move(sf::Vector2i dir, float deltaTime)
{
	//Restrict from anim changing
	if (!(status == SHOOT_ANIM || status == RELOAD_ANIM) || bodyAnim.isFinish())
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
	playerFeetRect.setPosition(entityRect.getPosition().x, entityRect.getPosition().y + 20);
	movePos.x = 0.0f; movePos.y = 0.0f;
}

bool Player::Shoot()
{
	if (allowShoot && holdAmmo > 0)
	{
		holdAmmo--;
		allowShoot = false;
		status = SHOOT_ANIM;
		return true;
	}
	
	return false;
}

void Player::Reload()
{
	holdAmmo = 18;
	status = RELOAD_ANIM;
}


void Player::Update(float deltaTime)
{
	//Change animation based on status
	//TODO
	std::cout << status << std::endl;
	switch (status)
	{
	case IDLE_ANIM:
		{
			bodyAnim.Update(deltaTime, 0, 0.1f, 20);
			playerRect.setTextureRect(*bodyAnim.getTexture());

			feetAnim.Update(deltaTime, 0, 1, 21, 20, true);
			playerFeetRect.setTextureRect(*feetAnim.getTexture());
		} break;
	case WALK_ANIM: {
		bodyAnim.Update(deltaTime, 1, 0.05f, 20);
		playerRect.setTextureRect(*bodyAnim.getTexture());

		feetAnim.Update(deltaTime, 0, 0.05f, 20);
		playerFeetRect.setTextureRect(*feetAnim.getTexture());
	} break;
	case SHOOT_ANIM: {
		bodyAnim.Update(deltaTime, 2, 0.05f, 18, 16);
		playerRect.setTextureRect(*bodyAnim.getTexture());
	} break;
	case RELOAD_ANIM: {
		bodyAnim.Update(deltaTime, 2, 0.05f, 15);
		playerRect.setTextureRect(*bodyAnim.getTexture());
	} break;
	default: break;
	}

	//Set back
	if (!(status == SHOOT_ANIM || status == RELOAD_ANIM) || bodyAnim.isFinish())
		status = IDLE_ANIM;
}

void Player::lookAt(const sf::Vector2f& mousePos)
{
	const float PI = 3.14159265f;

	const sf::Vector2f dir(mousePos.x - playerRect.getPosition().x,
		mousePos.y - playerRect.getPosition().y);
	
	angle = (atan2(dir.y, dir.x)) * 180 / PI;

	dirVect = dir / sqrt(pow(dir.x, 2) + pow(dir.y, 2));

	playerRect.setRotation(angle);
	playerFeetRect.setRotation(angle);
}

void Player::updateAllowShoot(float deltaTime)
{
	elapsedShootTime += deltaTime;
	if (elapsedShootTime >= shootCooldown && holdAmmo > 0)
	{
		allowShoot = true;
		elapsedShootTime = 0;
	}
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

sf::RectangleShape* Player::getFeetDraw()
{
	return &playerFeetRect;
}
