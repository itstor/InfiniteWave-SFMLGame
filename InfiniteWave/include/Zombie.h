#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <stack>

#include "Entity.h"
#include "Animation.h"
#include "Node.h"
#include "PathRequestManager.h"

class Zombie: public Entity
{
public:
	Zombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, PathRequestManager& mRequestManager);
	~Zombie() override;

	void Update(float deltaTime, const sf::Vector2f& distance);
	void setPosition(const sf::Vector2f& pos);
	void setWalkPath(std::stack<Node> walk_path);

	void Move(float deltaTime);
	void Attack();
	void getHit();

	bool isAllowAttack() const;

	sf::Vector2f getPosition() const;

	bool allowUpdatePath = true;

protected:
	PathRequestManager& mRequestManager;
	void lookAt(const sf::Vector2f& target_position);
	
	sf::Texture& zombieTex;
	Animation zombieAnim;
	sf::Vector2f mDirVect;
	sf::Vector2f nextPosition;
	std::stack<Node> mWalkPath;
	unsigned short int animState;
	bool allowAttack = true;
	bool isWalkPathChanged = false;
	float attackCooldown = 5.0f;
	float attackElapsedTime = 0.0f;
	float pathUpdateDelay = 2.0f;
};

#endif