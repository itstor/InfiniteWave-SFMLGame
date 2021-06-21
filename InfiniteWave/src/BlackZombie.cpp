#include "BlackZombie.h"
#include "..\include\BlackZombie.h"

BlackZombie::BlackZombie(const sf::Vector2f & pos, sf::Texture& zombie_tex): Zombie(pos, zombie_tex)
{
	health = 350.0f;
	movementSpeed = 250.0f;
}
