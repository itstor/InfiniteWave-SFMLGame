#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "GameObject.h"

class Collision
{
public:
	Collision() = default;

	void Setup(sf::RectangleShape& colBody);
	void Setup(sf::Vector2f colSize, sf::Vector2f position);
	
	bool onCollision(GameObject& other) const;

	sf::RectangleShape* getBody();
	
private:
	sf::RectangleShape colBody;
};

