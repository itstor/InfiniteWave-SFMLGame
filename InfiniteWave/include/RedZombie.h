#pragma once
#include "Zombie.h"

class RedZombie final: public Zombie
{
public:
	RedZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, PathRequestManager& path_request);
};

