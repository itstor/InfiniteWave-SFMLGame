#pragma once
#include "GameObject.h"

class Obstacle;

enum MoveDir { UP = 0, DOWN = 1, RIGHT = 2, LEFT = 3 };
enum AnimState { IDLE_ANIM = 0, WALK_ANIM = 1, SHOOT_ANIM = 2, RELOAD_ANIM = 3, ATTACK_ANIM = 4};

class Entity : public GameObject
{
public:
	virtual void Move(int dir, float deltaTime) = 0;
	void checkCollision(Obstacle& obs);
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

