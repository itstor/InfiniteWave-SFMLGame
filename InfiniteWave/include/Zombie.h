#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <stack>

#include "Entity.h"
#include "Node.h"
#include "PathRequestManager.h"
#include <SFML/Audio/Sound.hpp>

#include "SpriteAnimation.h"

enum class ZombieType {NORMAL_ZOMBIE, RED_ZOMBIE, BLUE_ZOMBIE, BLACK_ZOMBIE};

class Zombie: public Entity
{
public:
	Zombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, sf::Texture& blood_tex, PathRequestManager& request_manager, sf::SoundBuffer& sound_buffer);
	~Zombie() override;

	void Update(float deltaTime, const sf::Vector2f& distance);
	void setPosition(const sf::Vector2f& pos);
	void setWalkPath(std::stack<Node> walk_path);

	void Move(float deltaTime);
	void Attack();
	void getHit();

	bool isAllowAttack() const;

	sf::Vector2f getPosition() const;
	ZombieType getZombieType() const;
	sf::RectangleShape* getBloodDraw();


	bool allowUpdatePath = true;

private:
	void lookAt(const sf::Vector2f& target_position);

	PathRequestManager& mRequestManager;

	sf::Sound mZombieSound;
	sf::SoundBuffer& mZombieSoundBuffer;
	
	sf::Texture& zombieTex;
	sf::Texture& bloodSplashTex;
	SpriteAnimation zombieAnim;
	SpriteAnimation bloodAnim;
	AnimState animState;

	sf::RectangleShape bloodRect;

	sf::Vector2f mDirVect;
	sf::Vector2f nextPosition;
	std::stack<Node> mWalkPath;
	
	bool allowAttack = true;
	bool showBlood = false;

	float zombieSoundDelay = 0.0f;
	float attackCooldown = 5.0f;
	float pathUpdateDelay = 2.0f;

protected:
	ZombieType mZombieType;
};
#endif