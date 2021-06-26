#include "BlackZombie.h"

BlackZombie::BlackZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, PathRequestManager& path_request): Zombie(pos, zombie_tex, path_request)
{
	health = 350.0f;
	movementSpeed = 250.0f;
}
