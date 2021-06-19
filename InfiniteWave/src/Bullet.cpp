#include "Bullet.h"

Bullet::Bullet(): currentVelo(0.0f, 0.0f), max_speed_(5000.0f)
{
	bullet.setRadius(5.0f);
	bullet.setFillColor(sf::Color::Red);
}

void Bullet::Move(float deltaTime)
{
	bullet.move(currentVelo * deltaTime);
}

void Bullet::setDir(sf::Vector2f dirVect)
{
	currentVelo = dirVect * max_speed_;
}

void Bullet::setStartPos(sf::Vector2f pos)
{
	bullet.setPosition(pos);
	startPosition = pos;
}

sf::Vector2f Bullet::getPosition() const
{
	return bullet.getPosition();
}

bool Bullet::onCollision(GameObject & other) const
{
	const sf::FloatRect selfBounds = bullet.getGlobalBounds();

	if (const sf::FloatRect otherBounds = other.getCollider()->getGlobalBounds(); otherBounds.intersects(selfBounds))
	{
		return true;
	}

	return false;
}


sf::CircleShape* Bullet::getDraw()
{
	return &bullet;
}
