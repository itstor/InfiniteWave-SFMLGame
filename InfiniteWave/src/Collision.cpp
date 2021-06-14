#include "Collision.h"
#include "GameObject.h"

void Collision::Setup(sf::RectangleShape & colBody)
{
	this->colBody = colBody;
}

void Collision::Setup(sf::Vector2f colSize, sf::Vector2f position)
{
	colBody.setSize(colSize);
	colBody.setPosition(position);
	this->position = position;
}


bool Collision::onCollision(GameObject& other) const
{
	const sf::FloatRect selfBounds = colBody.getGlobalBounds();

	if (const sf::FloatRect otherBounds = other.getBody()->getGlobalBounds(); otherBounds.intersects(selfBounds))
	{
		return true;
	}
	
	return false;
}

sf::RectangleShape* Collision::getBody()
{
	return &colBody;
}
