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
