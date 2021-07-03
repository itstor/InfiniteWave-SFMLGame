#pragma once
#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "GameObject.h"


class Obstacle final : public GameObject
{
public:
	Obstacle(const sf::Vector2f& position, const sf::Vector2f& size);
};

#endif