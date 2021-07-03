#include "GameObject.h"

sf::RectangleShape * GameObject::GetCollider()
{
	return &mColliderBody;
}

bool GameObject::OnCollision(GameObject & other) const
{
	const sf::FloatRect selfBounds = mColliderBody.getGlobalBounds();

	if (const sf::FloatRect otherBounds = other.GetCollider()->getGlobalBounds(); otherBounds.intersects(selfBounds))
	{
		return true;
	}
	
	return false;
}

bool GameObject::OnCollision(const sf::RectangleShape & other) const
{
	const sf::FloatRect otherBounds = other.getGlobalBounds();
	if (const sf::FloatRect selfBounds = mColliderBody.getGlobalBounds(); selfBounds.intersects(otherBounds))
	{
		return true;
	}

	return false;
}
