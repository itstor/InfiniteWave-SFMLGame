#include "Obstacle.h"

void Obstacle::Create(sf::Vector2f position, sf::Vector2f size)
{
	this->position = position;
	this->ColliderBody.setPosition(this->position);
	this->ColliderBody.setSize(size);
}

