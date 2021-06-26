#include "NormalZombie.h"


NormalZombie::NormalZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, PathRequestManager& path_request): Zombie(pos, zombie_tex, path_request)
{
	health = 100.0f;
	movementSpeed = 350.0f;
}
