#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Entity.h"
#include "SpriteAnimation.h"


class Player final: public Entity
{
public:
	Player();

	void Update(float delta_time);
	void LookAt(const sf::Vector2f& mouse_pos);
	void SetPosition(const sf::Vector2f& pos);
	void IncreaseHealth(int amount);
	void GetHit(int damage);

	//In-game function
	void MoveDirection(MoveDir dir, float delta_time);
	void PlayerMove();
	bool Shoot();
	void Reload();

	//Getter
	int GetAmmo() const;
	float GetAngle() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f* GetDirVect();
	sf::RectangleShape* GetFeetDraw();

private:
	bool allowShoot = true;	
	unsigned short int holdAmmo = 18;	
	float elapsedShootTime = 0.0f;
	float shootCooldown = 0.5f;

	sf::Vector2f mDirVector;
	AnimState mBodyAnimState;
	AnimState mFeetAnimState;
	sf::Texture mBodyTex;
	sf::Texture mFeetTex;
	sf::RectangleShape& mPlayerRect;
	sf::RectangleShape mPlayerFeetRect;
	SpriteAnimation mBodyAnim;
	SpriteAnimation mFeetAnim;
};
	

#endif