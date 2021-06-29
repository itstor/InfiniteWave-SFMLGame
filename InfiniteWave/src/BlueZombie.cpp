#include "BlueZombie.h"

BlueZombie::BlueZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, PathRequestManager& path_request, sf::SoundBuffer& sound_buffer): Zombie(pos, zombie_tex, path_request, sound_buffer)
{
	health = 200.0f;
	movementSpeed = 400.0f;
	mZombieType = ZombieType::BLUE_ZOMBIE;

}

