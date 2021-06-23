#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

class GameObject
{
public:
	virtual ~GameObject() = default;
	
	virtual bool onCollision(GameObject& other) const;
	bool onCollision(const sf::RectangleShape& other) const;
	sf::RectangleShape* getCollider();
protected:
	sf::RectangleShape ColliderBody;
	sf::Vector2f position;
};
