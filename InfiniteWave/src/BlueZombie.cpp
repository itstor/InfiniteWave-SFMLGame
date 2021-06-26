#include "BlueZombie.h"

BlueZombie::BlueZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, PathRequestManager& path_request): Zombie(pos, zombie_tex, path_request)
{
	health = 200.0f;
	movementSpeed = 400.0f;
}

