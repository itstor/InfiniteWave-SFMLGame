#include "BlackZombie.h"

BlackZombie::BlackZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, PathRequestManager& path_request, sf::SoundBuffer& sound_buffer): Zombie(pos, zombie_tex, path_request, sound_buffer)
{
	health = 350.0f;
	movementSpeed = 250.0f;
	mZombieType = ZombieType::BLACK_ZOMBIE;

}
