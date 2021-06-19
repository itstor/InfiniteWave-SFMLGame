#pragma once
#include "GameObject.h"

class Obstacle final : public GameObject
{
public:
	Obstacle(const sf::Vector2f& position, const sf::Vector2f& size);
};

