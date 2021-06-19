#include "Obstacle.h"

Obstacle::Obstacle(const sf::Vector2f & position, const sf::Vector2f & size)
{
	this->position = position;
	ColliderBody.setPosition(this->position);
	ColliderBody.setSize(size);
	ColliderBody.setOutlineColor(sf::Color::Red);
	ColliderBody.setOutlineThickness(1);
	ColliderBody.setFillColor(sf::Color::Transparent);
}
