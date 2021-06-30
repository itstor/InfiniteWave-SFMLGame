#include "BlueZombie.h"

BlueZombie::BlueZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, sf::Texture& blood_tex, PathRequestManager& path_request, sf::SoundBuffer& sound_buffer): Zombie(pos, zombie_tex,blood_tex, path_request, sound_buffer)
{
	health = 200;
	movementSpeed = 400.0f;
	mZombieType = ZombieType::BLUE_ZOMBIE;

}

