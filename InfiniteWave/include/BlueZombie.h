#pragma once
#include "Zombie.h"

class BlueZombie final :public Zombie
{
public:
	BlueZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, PathRequestManager& path_request, sf::SoundBuffer& sound_buffer);
};

