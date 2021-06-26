#pragma once
#include "Zombie.h"

class NormalZombie final: public Zombie
{
public:
	NormalZombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, PathRequestManager& path_request);
};

