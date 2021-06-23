#include "Zombie.h"

#include <iostream>

Zombie::Zombie(const sf::Vector2f& pos, sf::Texture& zombie_tex): zombieTex(zombie_tex)
{
	ColliderBody.setSize({288,311});
	ColliderBody.setOrigin(ColliderBody.getSize() * 0.5f);
	entityRect.setSize({ 288,311 });
	entityRect.setOrigin(entityRect.getSize() * 0.5f);

	//setup anim
	//TODO change texture to load from memory
	entityRect.setTexture(&zombieTex);
	zombieAnim.Setup(&zombieTex, 2, 17);

	setPosition(pos);
}

Zombie::~Zombie(){
	std::cout << "DEADDDDD\n";
};

void Zombie::Update(float deltaTime, const sf::Vector2f& distance)
{
	if (!(animState == ATTACK_ANIM) || zombieAnim.isFinish())
		animState = WALK_ANIM;
	
	if (animState == WALK_ANIM)
	{
		zombieAnim.Update(deltaTime, 0, 0.05f, 0, 17);
		entityRect.setTextureRect(*zombieAnim.getTexture());
	}
	else if(animState == ATTACK_ANIM)
	{
		zombieAnim.Update(deltaTime, 1, 0.1f,0, 9);
		entityRect.setTextureRect(*zombieAnim.getTexture());
	}

	attackElapsedTime += deltaTime;
	if (attackElapsedTime >= attackCooldown)
	{
		allowAttack = true;
		attackElapsedTime = 0;
	}
}

void Zombie::setPosition(const sf::Vector2f& pos)
{
	entityRect.setPosition(pos);
	ColliderBody.setPosition(pos);
}

void Zombie::Move(MoveDir dir, float deltaTime)
{
	
}

void Zombie::Attack()
{
	allowAttack = false;
	std::cout << "HRGHHH\n";
	animState = ATTACK_ANIM;
	//play attack anim
}

void Zombie::getHit()
{
	health -= 20;
	std::cout << "ARGHH\n";
	if (health <= 0)
	{
		std::cout << "DEAD AGAIN\n";
		misDead = true;
	}
}

bool Zombie::isAllowAttack() const
{
	return allowAttack;
}

sf::Vector2f Zombie::getPosition() const
{
	return entityRect.getPosition();
}


