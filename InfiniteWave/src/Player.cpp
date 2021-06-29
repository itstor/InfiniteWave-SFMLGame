#define _USE_MATH_DEFINES

#include "Player.h"

#include <cmath>
#include <iostream>
#include <SFML/Audio/Listener.hpp>
#include <SFML/Window/Mouse.hpp>



Player::Player(): playerRect(entityRect)
{
	//setup player
	movementSpeed = 400.0f;
	health = 200.0f;
	
	//setup animation texture
	bodyTex.loadFromFile("Assets/Texture/Sprites/Player/playerspites.png");
	bodyTex.setSmooth(true);
	playerRect.setTexture(&bodyTex);

	feetTex.loadFromFile("Assets/Texture/Sprites/Player/feetplayer.png");
	feetTex.setSmooth(true);
	playerFeetRect.setTexture(&feetTex);

	ColliderBody.setSize(sf::Vector2f(100, 100));
	ColliderBody.setOrigin(50, 50);
	playerRect.setSize(sf::Vector2f(253, 216));
	playerRect.setOrigin(98, 119);
	playerFeetRect.setSize(sf::Vector2f(172, 124));
	playerFeetRect.setOrigin(86, 62);
	sf::Listener::setPosition(playerRect.getPosition().x, 0, playerRect.getPosition().y);
	

	//init animation
	bodyAnim.Setup(&bodyTex, 3, 20);
	feetAnim.Setup(&feetTex, 1, 21);
}

void Player::MoveDirection(MoveDir dir, float deltaTime)
{
	feetAnimState = AnimState::WALK_ANIM;
	//Restrict from anim changing
	if (!(bodyAnimState == AnimState::SHOOT_ANIM || bodyAnimState == AnimState::RELOAD_ANIM) || bodyAnim.isFinish())
		bodyAnimState = AnimState::WALK_ANIM;
	
	if (dir == MoveDir::LEFT) //Left
	{
		movePos.x = -movementSpeed * deltaTime;
	}
	if (dir == MoveDir::RIGHT) //Right
	{
		movePos.x = movementSpeed * deltaTime;
	}
	if (dir == MoveDir::UP) //Up
	{
		movePos.y = -movementSpeed * deltaTime;
	}
	if (dir == MoveDir::DOWN) //Down
	{
		movePos.y = movementSpeed * deltaTime;
	}
}

void Player::PlayerMove()
{
	if (movePos.x != 0 && movePos.y != 0) //If player move directional
		movePos *= 0.7f;

	entityRect.move(movePos);
	ColliderBody.move(movePos);
	playerFeetRect.setPosition(entityRect.getPosition().x, entityRect.getPosition().y + 20);
	sf::Listener::setPosition(playerRect.getPosition().x, 0, playerRect.getPosition().y);
	movePos.x = 0.0f; movePos.y = 0.0f;
}

bool Player::Shoot()
{
	if (allowShoot && holdAmmo > 0)
	{
		holdAmmo--;
		allowShoot = false;
		bodyAnimState = AnimState::SHOOT_ANIM;
		return true;
	}
	
	return false;
}

int Player::getAmmo() const
{
	return holdAmmo;
}

void Player::Reload()
{
	holdAmmo = 18;
	bodyAnimState = AnimState::RELOAD_ANIM;
}


void Player::Update(float deltaTime)
{
	//Change animation based on state

	//body
	if (bodyAnimState == AnimState::IDLE_ANIM)
	{
		bodyAnim.Update(deltaTime, 0, 0.1f, 0, 20);
		playerRect.setTextureRect(*bodyAnim.getTexture());
	}
	else if(bodyAnimState == AnimState::WALK_ANIM)
	{
		bodyAnim.Update(deltaTime, 1, 0.05f,0, 20);
		playerRect.setTextureRect(*bodyAnim.getTexture());
	}
	else if(bodyAnimState == AnimState::SHOOT_ANIM)
	{
		bodyAnim.Update(deltaTime, 2, 0.05f, 16, 18);
		playerRect.setTextureRect(*bodyAnim.getTexture());
	}
	else if(bodyAnimState == AnimState::RELOAD_ANIM)
	{
		bodyAnim.Update(deltaTime, 2, 0.05f,0, 15);
		playerRect.setTextureRect(*bodyAnim.getTexture());
	}

	//feet
	if (feetAnimState == AnimState::IDLE_ANIM)
	{
		feetAnim.Hide();
		playerFeetRect.setTextureRect(*feetAnim.getTexture());
	}
	else if (feetAnimState == AnimState::WALK_ANIM)
	{
		feetAnim.Update(deltaTime, 0, 0.05f,0, 20);
		playerFeetRect.setTextureRect(*feetAnim.getTexture());
	}

	//Set back
	feetAnimState = AnimState::IDLE_ANIM;

	if (!(bodyAnimState == AnimState::SHOOT_ANIM || bodyAnimState == AnimState::RELOAD_ANIM) || bodyAnim.isFinish())
		bodyAnimState = AnimState::IDLE_ANIM;

	//Update player shoot cooldown
	elapsedShootTime += deltaTime;
	if (elapsedShootTime >= shootCooldown && holdAmmo > 0)
	{
		allowShoot = true;
		elapsedShootTime = 0;
	}

	//death
	if (health <= 0.0f)
	{
		misDead = true;
	}
}

void Player::lookAt(const sf::Vector2f& mousePos)
{
	const sf::Vector2f dir(mousePos.x - playerRect.getPosition().x,
		mousePos.y - playerRect.getPosition().y);
	
	angle = (atan2(dir.y, dir.x)) * 180 / static_cast<float>(M_PI);

	dirVect = dir / sqrt(pow(dir.x, 2) + pow(dir.y, 2));

	playerRect.setRotation(angle);
	playerFeetRect.setRotation(angle);
}

void Player::setPosition(const sf::Vector2f & pos)
{
	playerRect.setPosition(pos);
	playerFeetRect.setPosition(pos);
	ColliderBody.setPosition(pos);
	sf::Listener::setPosition(playerRect.getPosition().x, 0, playerRect.getPosition().y);
}

void Player::getHit()
{
	const float damage = rand() % 10 + 5;
	health -= damage;
	std::cout << "UGHHH\n";
	//TODO play blinking animation
}

sf::Vector2f Player::getPosition() const
{
	return playerRect.getPosition();
}

float Player::getAngle() const
{
	return angle;
}

sf::Vector2f* Player::getDirVect()
{
	return &dirVect;
}

sf::RectangleShape* Player::getFeetDraw()
{
	return &playerFeetRect;
}
