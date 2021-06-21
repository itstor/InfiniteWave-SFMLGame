#include "RedZombie.h"

RedZombie::RedZombie(const sf::Vector2f pos, sf::Texture& zombie_tex): Zombie(pos, zombie_tex)
{
	health = 150.0f;
	movementSpeed = 250.0f;
}
