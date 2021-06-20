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

	void Move(int dir, float deltaTime) override;
	void Attack();
	void getHit();

	sf::Vector2f getPosition() const;

private:
	sf::Texture zombieTex;
	Animation zombieAnim;
	
};

