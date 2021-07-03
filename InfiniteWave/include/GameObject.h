#pragma once
#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <SFML/Graphics/RectangleShape.hpp>


class GameObject
{
public:
	virtual ~GameObject() = default;
	
	virtual bool OnCollision(GameObject& other) const;
	bool OnCollision(const sf::RectangleShape& other) const;
	
	sf::RectangleShape* GetCollider();

protected:
	sf::RectangleShape mColliderBody;
	sf::Vector2f mPosition;
};

#endif
