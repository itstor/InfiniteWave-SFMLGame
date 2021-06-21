#include "BlueZombie.h"

BlueZombie::BlueZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex): Zombie(pos, zombie_tex)
{
	health = 200.0f;
	movementSpeed = 400.0f;
}

