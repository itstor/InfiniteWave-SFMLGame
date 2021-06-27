#pragma once
#include "GameObject.h"

class Obstacle;

enum class MoveDir { UP, DOWN, RIGHT, LEFT};
enum class AnimState { IDLE_ANIM, WALK_ANIM, SHOOT_ANIM, RELOAD_ANIM, ATTACK_ANIM};

class Entity : public GameObject
{
public:
	void CheckCollision(Obstacle& obs);
	float getHealth() const;
	bool isDead() const;
	
	sf::RectangleShape* getDraw();

protected:
	sf::RectangleShape entityRect;
	sf::Vector2f movePos;
	float movementSpeed = 0;
	
	float health = 0;
	float angle = 0;
	bool misDead = false;
};

