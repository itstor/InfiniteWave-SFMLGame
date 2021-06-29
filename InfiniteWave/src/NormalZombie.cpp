#include "NormalZombie.h"


NormalZombie::NormalZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, PathRequestManager& path_request, sf::SoundBuffer& sound_buffer): Zombie(pos, zombie_tex, path_request, sound_buffer)
{
	health = 100.0f;
	movementSpeed = 350.0f;
	mZombieType = ZombieType::NORMAL_ZOMBIE;

}
