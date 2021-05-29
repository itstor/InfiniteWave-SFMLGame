#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/System.hpp>

namespace ph
{
	float g = 0.0f;

	void parabolic(sf::Vector2f& pos, float time);
}

#endif


