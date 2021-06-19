#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include "GameObject.h"

class Bullet: public GameObject
{
public:
	Bullet();
	
	void Move(float deltaTime);
	void setDir(sf::Vector2f dirVect);
	void setStartPos(sf::Vector2f pos);
	sf::Vector2f getPosition() const;
	bool onCollision(GameObject& other) const override;
	
	sf::CircleShape* getDraw();
	sf::Vector2f startPosition;
private:
	sf::CircleShape bullet;
	sf::Vector2f currentVelo;
	float max_speed_;
};

