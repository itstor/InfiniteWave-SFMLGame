#include "Entity.h"

#include <iostream>

#include "Obstacle.h"

void Entity::CheckCollision(Obstacle& obs)
{
	const sf::FloatRect entityBounds = ColliderBody.getGlobalBounds();
	const sf::FloatRect obstacleBounds = obs.getCollider()->getGlobalBounds();

	sf::FloatRect nextPosition = entityBounds;
	nextPosition.left += movePos.x;
	nextPosition.top += movePos.y;

	if (obstacleBounds.intersects(nextPosition))
	{
		//TOP
		if (entityBounds.top < obstacleBounds.top &&
			entityBounds.left < obstacleBounds.left + obstacleBounds.width &&
			entityBounds.left + entityBounds.width > obstacleBounds.left)
		{
			//std::cout << "Collided TOP\n";
			movePos.y = 0.0f;
		}
		//BOTTOM
		else if (entityBounds.top > obstacleBounds.top &&
			entityBounds.left < obstacleBounds.left + obstacleBounds.width &&
			entityBounds.left + entityBounds.width > obstacleBounds.left)
		{
			//std::cout << "Collided BOTTOM\n";
			movePos.y = 0.0f;
		}
		//LEFT
		if (entityBounds.left < obstacleBounds.left &&
			entityBounds.top < obstacleBounds.top + obstacleBounds.height &&
			entityBounds.top + entityBounds.height > obstacleBounds.top)
		{
			//std::cout << "Collided LEFT\n";
			movePos.x = 0.0f;
		}
		//RIGHT
		else if (entityBounds.left > obstacleBounds.left &&
			entityBounds.top < obstacleBounds.top + obstacleBounds.height &&
			entityBounds.top + entityBounds.height > obstacleBounds.top)
		{
			//std::cout << "Collided RIGHT\n";
			movePos.x = 0.0f;
		}
	}
}

float Entity::getHealth() const
{
	return health;
}

bool Entity::isDead() const
{
	return misDead;
}

sf::RectangleShape* Entity::getDraw()
{
	return &entityRect;
}
