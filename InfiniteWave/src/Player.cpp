#include "Player.h"

#include <cmath>
#include <iostream>
#include <SFML/Window/Mouse.hpp>


Player::Player(): playerRect(entityRect)
{
	//setup player
	movementSpeed = 150.0f;
	
	ColliderBody.setSize(sf::Vector2f(117, 142));
	ColliderBody.setOrigin(59, 71);
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
	feetAnimState = WALK_ANIM;
	//Restrict from anim changing
	if (!(bodyAnimState == SHOOT_ANIM || bodyAnimState == RELOAD_ANIM) || bodyAnim.isFinish())
		bodyAnimState = WALK_ANIM;
	
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
		bodyAnimState = SHOOT_ANIM;
		return true;
	}
	
	return false;
}

void Player::Reload()
{
	holdAmmo = 18;
	bodyAnimState = RELOAD_ANIM;
}


void Player::Update(float deltaTime)
{
	//Change animation based on state

	//body
	if (bodyAnimState == IDLE_ANIM)
	{
		bodyAnim.Update(deltaTime, 0, 0.1f, 0, 20);
		playerRect.setTextureRect(*bodyAnim.getTexture());
	}
	else if(bodyAnimState == WALK_ANIM)
	{
		bodyAnim.Update(deltaTime, 1, 0.05f,0, 20);
		playerRect.setTextureRect(*bodyAnim.getTexture());
	}
	else if(bodyAnimState == SHOOT_ANIM)
	{
		bodyAnim.Update(deltaTime, 2, 0.05f, 16, 18);
		playerRect.setTextureRect(*bodyAnim.getTexture());
	}
	else if(bodyAnimState == RELOAD_ANIM)
	{
		bodyAnim.Update(deltaTime, 2, 0.05f,0, 15);
		playerRect.setTextureRect(*bodyAnim.getTexture());
	}

	//feet
	if (feetAnimState == IDLE_ANIM)
	{
		feetAnim.Hide();
		playerFeetRect.setTextureRect(*feetAnim.getTexture());
	}
	else if (feetAnimState == WALK_ANIM)
	{
		feetAnim.Update(deltaTime, 0, 0.05f,0, 20);
		playerFeetRect.setTextureRect(*feetAnim.getTexture());
	}

	//Set back
	feetAnimState = IDLE_ANIM;

	if (!(bodyAnimState == SHOOT_ANIM || bodyAnimState == RELOAD_ANIM) || bodyAnim.isFinish())
		bodyAnimState = IDLE_ANIM;
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
