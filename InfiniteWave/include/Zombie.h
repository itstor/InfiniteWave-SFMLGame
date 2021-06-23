#pragma once
#include "Entity.h"
#include "Animation.h"

class Zombie: public Entity
{
public:
	Zombie(const sf::Vector2f& pos, sf::Texture& zombie_tex);
	~Zombie() override;

	void Update(float deltaTime, const sf::Vector2f& distance);
	void lookAt();
	void updateAllowAttack(float deltaTime);
	void setPosition(const sf::Vector2f& pos);

	void Move(MoveDir dir, float deltaTime) override;
	void Attack();
	void getHit();

	bool isAllowAttack() const;

	sf::Vector2f getPosition() const;

protected:
	sf::Texture& zombieTex;
	Animation zombieAnim;

	unsigned short int animState;
	bool allowAttack = true;
	float attackCooldown = 5.0f;
	float attackElapsedTime = 0.0f;
};

