#pragma once
#include "GameObject.h"

class Obstacle;

class Entity : public GameObject
{
public:
	Entity() = default;
	
	virtual void Move(sf::Vector2i dir, float deltaTime) = 0;
	void checkCollision(Obstacle& obs, float deltaTime);

	sf::RectangleShape* getDraw();

protected:
	sf::RectangleShape entityRect;
	sf::Vector2f velocity;
	float movementSpeed;
	
	float health = 0;
	float angle = 0;
	bool isDead = false;
};

