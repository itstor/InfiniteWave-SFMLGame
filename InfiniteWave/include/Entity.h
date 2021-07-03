#pragma once
#ifndef ENTITY_H_
#define ENTITY_H_

#include "GameObject.h"

class Obstacle;

enum class MoveDir { UP, DOWN, RIGHT, LEFT};
enum class AnimState { IDLE_ANIM, WALK_ANIM, SHOOT_ANIM, RELOAD_ANIM, ATTACK_ANIM};


class Entity : public GameObject
{
public:
	void CheckCollision(Obstacle& obs);
	
	float GetHealth() const;
	bool IsDead() const;
	
	sf::RectangleShape* GetDraw();

protected:
	float mMovementSpeed = 0;
	int mHealth = 0;
	float mAngle = 0;
	bool mIsDead = false;
	
	sf::RectangleShape mEntityRect;
	sf::Vector2f mMovePos;
};

#endif

