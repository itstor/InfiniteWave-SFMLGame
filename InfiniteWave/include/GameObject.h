#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	bool onCollision(GameObject& other) const;
	sf::RectangleShape* getCollider();
protected:
	sf::RectangleShape ColliderBody;
	sf::Vector2f position;
};

