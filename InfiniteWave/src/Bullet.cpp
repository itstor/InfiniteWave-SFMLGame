#include "Bullet.h"

Bullet::Bullet(): mCurrentVelocity(0.0f, 0.0f), mMaxSpeed(5000.0f)
{
	mBulletShape.setRadius(5.0f);
	mBulletShape.setFillColor(sf::Color::Red);
}

void Bullet::Move(float delta_time)
{
	mBulletShape.move(mCurrentVelocity * delta_time);
}

void Bullet::SetDirection(sf::Vector2f dir_vector)
{
	mCurrentVelocity = dir_vector * mMaxSpeed;
}

void Bullet::SetStartPos(sf::Vector2f position)
{
	mBulletShape.setPosition(position);
	mStartPosition = position;
}

sf::Vector2f Bullet::GetPosition() const
{
	return mBulletShape.getPosition();
}

bool Bullet::OnCollision(GameObject & other) const
{
	const sf::FloatRect selfBounds = mBulletShape.getGlobalBounds();

	if (const sf::FloatRect otherBounds = other.GetCollider()->getGlobalBounds(); otherBounds.intersects(selfBounds))
	{
		return true;
	}

	return false;
}


sf::CircleShape* Bullet::GetDraw()
{
	return &mBulletShape;
}
