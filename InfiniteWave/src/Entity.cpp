#include "Entity.h"

#include <iostream>

#include "Obstacle.h"

void Entity::CheckCollision(Obstacle& obs)
{
	const sf::FloatRect entityBounds = mColliderBody.getGlobalBounds();
	const sf::FloatRect obstacleBounds = obs.GetCollider()->getGlobalBounds();

	sf::FloatRect nextPosition = entityBounds;
	nextPosition.left += mMovePos.x;
	nextPosition.top += mMovePos.y;

	if (obstacleBounds.intersects(nextPosition))
	{
		//TOP
		if (entityBounds.top < obstacleBounds.top &&
			entityBounds.left < obstacleBounds.left + obstacleBounds.width &&
			entityBounds.left + entityBounds.width > obstacleBounds.left)
		{
			//std::cout << "Collided TOP\n";
			mMovePos.y = 0.0f;
		}
		//BOTTOM
		else if (entityBounds.top > obstacleBounds.top &&
			entityBounds.left < obstacleBounds.left + obstacleBounds.width &&
			entityBounds.left + entityBounds.width > obstacleBounds.left)
		{
			//std::cout << "Collided BOTTOM\n";
			mMovePos.y = 0.0f;
		}
		//LEFT
		if (entityBounds.left < obstacleBounds.left &&
			entityBounds.top < obstacleBounds.top + obstacleBounds.height &&
			entityBounds.top + entityBounds.height > obstacleBounds.top)
		{
			//std::cout << "Collided LEFT\n";
			mMovePos.x = 0.0f;
		}
		//RIGHT
		else if (entityBounds.left > obstacleBounds.left &&
			entityBounds.top < obstacleBounds.top + obstacleBounds.height &&
			entityBounds.top + entityBounds.height > obstacleBounds.top)
		{
			//std::cout << "Collided RIGHT\n";
			mMovePos.x = 0.0f;
		}
	}
}

float Entity::GetHealth() const
{
	return mHealth;
}

bool Entity::IsDead() const
{
	return mIsDead;
}

sf::RectangleShape* Entity::GetDraw()
{
	return &mEntityRect;
}
