#include "NormalZombie.h"


NormalZombie::NormalZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex): Zombie(pos, zombie_tex)
{
	health = 100.0f;
	movementSpeed = 350.0f;
}
