#include "Obstacle.h"

Obstacle::Obstacle(const sf::Vector2f & position, const sf::Vector2f & size)
{
	this->mPosition = position;
	mColliderBody.setPosition(this->mPosition);
	mColliderBody.setSize(size);
	mColliderBody.setOutlineColor(sf::Color::Red);
	mColliderBody.setOutlineThickness(1);
	mColliderBody.setFillColor(sf::Color::Transparent);
}
