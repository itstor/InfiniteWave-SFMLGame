#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include "GameObject.h"

class Bullet: public GameObject
{
public:
	Bullet();
	
	void Move(float deltaTime);
	void setDir(sf::Vector2f dirVect);
	bool on_collision(GameObject& other) const;
	
	sf::CircleShape* getDraw();
private:
	sf::CircleShape bullet;
	sf::Vector2f currentVelo;
	float max_speed_;
};

