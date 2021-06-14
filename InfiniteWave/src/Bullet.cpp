#include "Bullet.h"
#include "..\include\Bullet.h"

Bullet::Bullet(): currentVelo(0.0f, 0.0f), max_speed_(1000.0f)
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

bool Bullet::on_collision(GameObject & other) const
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
