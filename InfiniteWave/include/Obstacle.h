#pragma once
#include "GameObject.h"

class Obstacle final : public GameObject
{
public:
	void Create(sf::Vector2f position, sf::Vector2f size);
};

