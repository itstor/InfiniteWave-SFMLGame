#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Animation.h"
#include "Entity.h"

class Player final: public Entity
{
public:
	Player();

	void Update(float deltaTime);
	void lookAt(const sf::Vector2f& mousePos);
	void setPosition(const sf::Vector2f& pos);
	void getHit();

	//In-game function
	void MoveDirection(MoveDir dir, float deltaTime);
	void PlayerMove();
	bool Shoot();
	void Reload();

	//Getter
	int getAmmo() const;
	float getAngle() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f* getDirVect();
	sf::RectangleShape* getFeetDraw();

private:
	sf::RectangleShape& playerRect;
	sf::RectangleShape playerFeetRect;
	
	Animation bodyAnim;
	Animation feetAnim;
	sf::Texture bodyTex;
	sf::Texture feetTex;
	AnimState bodyAnimState;
	AnimState feetAnimState;

	sf::Vector2f dirVect;

	bool allowShoot = true;
	
	unsigned short int holdAmmo = 18;
	
	float elapsedShootTime = 0.0f;
	float shootCooldown = 0.5f;
};

