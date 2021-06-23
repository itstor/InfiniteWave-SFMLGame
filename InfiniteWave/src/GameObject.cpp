#include "GameObject.h"

sf::RectangleShape * GameObject::getCollider()
{
	return &ColliderBody;
}

bool GameObject::onCollision(GameObject & other) const
{
	const sf::FloatRect selfBounds = ColliderBody.getGlobalBounds();

	if (const sf::FloatRect otherBounds = other.getCollider()->getGlobalBounds(); otherBounds.intersects(selfBounds))
	{
		return true;
	}
	
	return false;
}

bool GameObject::onCollision(const sf::RectangleShape & other) const
{
	const sf::FloatRect otherBounds = other.getGlobalBounds();
	if (const sf::FloatRect selfBounds = ColliderBody.getGlobalBounds(); selfBounds.intersects(otherBounds))
	{
		return true;
	}

	return false;
}
