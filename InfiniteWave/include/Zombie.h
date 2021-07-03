#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <stack>
#include <SFML/Audio/Sound.hpp>

#include "Node.h"
#include "Entity.h"
#include "SpriteAnimation.h"
#include "PathRequestManager.h"


enum class ZombieType {NORMAL_ZOMBIE, RED_ZOMBIE, BLUE_ZOMBIE, BLACK_ZOMBIE};

class Zombie: public Entity
{
public:
	Zombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, sf::Texture& blood_tex, PathRequestManager& request_manager, sf::SoundBuffer& sound_buffer);
	~Zombie() override;

	void Update(float delta_time, const sf::Vector2f& distance);
	void SetPosition(const sf::Vector2f& position);
	void SetWalkPath(std::stack<Node> walk_path);

	void Move(float deltaTime);
	void Attack();
	void GetHit();

	bool IsAllowAttack() const;

	sf::Vector2f GetPosition() const;
	ZombieType GetZombieType() const;
	sf::RectangleShape* GetBloodDraw();

	template <typename T>
	static std::unique_ptr<T> Spawn(const sf::Vector2f& pos, sf::Texture& zombie_tex, sf::Texture& blood_tex, PathRequestManager& request_manager, sf::SoundBuffer& sound_buffer);

protected:
	ZombieType mZombieType;

private:
	void LookAt(const sf::Vector2f& target_position);

	bool mAllowAttack = true;
	bool mShowBlood = false;
	float mZombieSoundDelay = 0.0f;
	float mAttackCooldown = 5.0f;
	float mPathUpdateDelay = 2.0f;
	
	PathRequestManager& mRequestManager;

	sf::Sound mZombieSound;
	sf::SoundBuffer& mZombieSoundBuffer;
	
	sf::Texture& mZombieTex;
	sf::Texture& mBloodSplashTex;
	SpriteAnimation mZombieAnim;
	SpriteAnimation mBloodAnim;
	AnimState mAnimState;

	sf::RectangleShape mBloodRect;

	sf::Vector2f mDirVector;
	sf::Vector2f mNextPosition;
	std::stack<Node> mWalkPath;
};

template<typename T>
std::unique_ptr<T> Zombie::Spawn(const sf::Vector2f & pos, sf::Texture & zombie_tex, sf::Texture & blood_tex, PathRequestManager & request_manager, sf::SoundBuffer & sound_buffer)
{
	return std::make_unique<T>(pos, zombie_tex, blood_tex, request_manager, sound_buffer);
}

#endif