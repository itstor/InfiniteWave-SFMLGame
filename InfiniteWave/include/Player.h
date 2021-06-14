#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Animation.h"
#include "Entity.h"

enum status { IDLE_ANIM = 0, WALK_ANIM = 1, SHOOT_ANIM = 2};

class Player : public Entity
{
public:
	Player();

	void Update(float deltaTime);
	void lookAt(sf::Vector2f mousePos);
	void updateAllowShoot(float deltaTime);

	//In-game function
	void Move(sf::Vector2i dir, float deltaTime) override;
	void PlayerMove();
	void Reload();
	
	sf::Vector2f getPosition() const;
	float getAngle() const;
	sf::Vector2f getDirVect() const;

	bool allowShoot = true;
	
	
private:
	unsigned short int status{};
	unsigned short int holdAmmo = 18;
	float elapsedShootTime = 0.0f;
	float shootCooldown = 0.5f;
	sf::Vector2f dirVect;

	sf::RectangleShape& playerRect;
	sf::Texture idleBodyTex;
	sf::Texture walkBodyTex;
	sf::Texture shootBodyTex;
	sf::Texture reloadBodyTex;
	
	sf::Texture idleFootTex;
	sf::Texture walkFootTex;
	sf::Texture shootFootTex;
	sf::Texture reloadFootTex;
};

