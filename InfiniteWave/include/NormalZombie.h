#pragma once
#ifndef NORMAL_ZOMBIE_H_
#define NORMAL_ZOMBIE_H_

#include "Zombie.h"

class NormalZombie final: public Zombie
{
public:
	NormalZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, sf::Texture& blood_tex, PathRequestManager& path_request, sf::SoundBuffer& sound_buffer);
};

#endif