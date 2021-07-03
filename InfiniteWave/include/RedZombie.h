#pragma once
#ifndef RED_ZOMBIE_H_
#define RED_ZOMBIE_H_

#include "Zombie.h"


class RedZombie final: public Zombie
{
public:
	RedZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, sf::Texture& blood_tex, PathRequestManager& path_request, sf::SoundBuffer& sound_buffer);
};

#endif