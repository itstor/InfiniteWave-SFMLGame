#pragma once
#ifndef BULLET_H_
#define BULLET_H_

#include <SFML/Graphics/CircleShape.hpp>

#include "GameObject.h"

class Bullet: public GameObject
{
public:
	Bullet();
	
	void Move(float delta_time);
	void SetDirection(sf::Vector2f dir_vector);
	bool OnCollision(GameObject& other) const override;
	void SetStartPos(sf::Vector2f position);
	
	sf::Vector2f GetPosition() const;
	sf::CircleShape* GetDraw();

	sf::Vector2f mStartPosition;
private:
	float mMaxSpeed;

	sf::CircleShape mBulletShape;
	sf::Vector2f mCurrentVelocity;
};

#endif