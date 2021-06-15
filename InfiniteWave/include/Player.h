#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Animation.h"
#include "Entity.h"

enum status { IDLE_ANIM = 0, WALK_ANIM = 1, SHOOT_ANIM = 2, RELOAD_ANIM = 3};

class Player : public Entity
{
public:
	Player();

	void Update(float deltaTime);
	void lookAt(const sf::Vector2f& mousePos);
	void updateAllowShoot(float deltaTime);

	//In-game function
	void Move(sf::Vector2i dir, float deltaTime) override;
	void PlayerMove();
	bool Shoot();
	void Reload();
	
	sf::Vector2f getPosition() const;
	float getAngle() const;
	sf::Vector2f getDirVect() const;
	sf::RectangleShape* getFeetDraw();

private:
	unsigned short int status{};
	unsigned short int holdAmmo = 18;
	float playerHealth = 100.0f;
	float elapsedShootTime = 0.0f;
	float shootCooldown = 0.5f;
	float playerSeekRadius = 500.0f;
	bool allowShoot = true;
	sf::Vector2f dirVect;

	Animation bodyAnim;
	Animation feetAnim;
	sf::Texture bodyTex;
	sf::Texture feetTex;

	sf::RectangleShape& playerRect;
	sf::RectangleShape playerFeetRect;
	
};

