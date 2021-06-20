#include "Zombie.h"

#include <iostream>

Zombie::Zombie(const sf::Vector2f& pos, sf::Texture& zombie_tex)
{
	health = 100.0f;
	movementSpeed = 350.0f;

	ColliderBody.setSize({288,311});
	ColliderBody.setOrigin(ColliderBody.getSize() * 0.5f);
	entityRect.setSize({ 288,311 });
	entityRect.setOrigin(entityRect.getSize() * 0.5f);

	//setup anim
	//TODO change texture to load from memory
	zombieTex = zombie_tex;
	entityRect.setTexture(&zombieTex);

	zombieAnim.Setup(&zombieTex, 2, 17);

	setPosition(pos);
}

Zombie::~Zombie() = default;

void Zombie::Update(float deltaTime, const sf::Vector2f& distance)
{
	zombieAnim.Update(deltaTime, 0, 0.05f, 0, 17);
	entityRect.setTextureRect(*zombieAnim.getTexture());
}

void Zombie::setPosition(const sf::Vector2f& pos)
{
	entityRect.setPosition(pos);
	ColliderBody.setPosition(pos);
}

void Zombie::Move(int dir, float deltaTime)
{
	
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


