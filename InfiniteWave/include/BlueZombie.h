#pragma once
#ifndef BLUE_ZOMBIE_H_
#define BLUE_ZOMBIE_H_

#include "Zombie.h"

class BlueZombie final :public Zombie
{
public:
	BlueZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, sf::Texture& blood_tex, PathRequestManager& path_request, sf::SoundBuffer& sound_buffer);
};

#endif