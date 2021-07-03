#define _USE_MATH_DEFINES

#include "Player.h"

#include <cmath>
#include <SFML/Audio/Listener.hpp>
#include <SFML/Window/Mouse.hpp>



Player::Player(): mPlayerRect(mEntityRect)
{
	//setup player
	mMovementSpeed = 400.0f;
	mHealth = 200;
	
	//setup animation texture
	mBodyTex.loadFromFile("data/Texture/Sprites/Player/playerspites.png");
	mBodyTex.setSmooth(true);
	mPlayerRect.setTexture(&mBodyTex);

	mFeetTex.loadFromFile("data/Texture/Sprites/Player/feetplayer.png");
	mFeetTex.setSmooth(true);
	mPlayerFeetRect.setTexture(&mFeetTex);

	mColliderBody.setSize(sf::Vector2f(100, 100));
	mColliderBody.setOrigin(50, 50);
	mPlayerRect.setSize(sf::Vector2f(253, 216));
	mPlayerRect.setOrigin(98, 119);
	mPlayerFeetRect.setSize(sf::Vector2f(172, 124));
	mPlayerFeetRect.setOrigin(86, 62);
	sf::Listener::setPosition(mPlayerRect.getPosition().x, 0, mPlayerRect.getPosition().y);
	

	//init animation
	mBodyAnim.Setup(&mBodyTex, 3, 20);
	mFeetAnim.Setup(&mFeetTex, 1, 21);
}

void Player::MoveDirection(MoveDir dir, float delta_time)
{
	mFeetAnimState = AnimState::WALK_ANIM;
	//Restrict from anim changing
	if (!(mBodyAnimState == AnimState::SHOOT_ANIM || mBodyAnimState == AnimState::RELOAD_ANIM) || mBodyAnim.IsFinish())
		mBodyAnimState = AnimState::WALK_ANIM;
	
	if (dir == MoveDir::LEFT) //Left
	{
		mMovePos.x = -mMovementSpeed * delta_time;
	}
	if (dir == MoveDir::RIGHT) //Right
	{
		mMovePos.x = mMovementSpeed * delta_time;
	}
	if (dir == MoveDir::UP) //Up
	{
		mMovePos.y = -mMovementSpeed * delta_time;
	}
	if (dir == MoveDir::DOWN) //Down
	{
		mMovePos.y = mMovementSpeed * delta_time;
	}
}

void Player::PlayerMove()
{
	if (mMovePos.x != 0 && mMovePos.y != 0) //If player move directional
		mMovePos *= 0.7f;

	mEntityRect.move(mMovePos);
	mColliderBody.move(mMovePos);
	mPlayerFeetRect.setPosition(mEntityRect.getPosition().x, mEntityRect.getPosition().y + 20);
	sf::Listener::setPosition(mPlayerRect.getPosition().x, 0, mPlayerRect.getPosition().y);
	mMovePos.x = 0.0f; mMovePos.y = 0.0f;
}

bool Player::Shoot()
{
	if (allowShoot && holdAmmo > 0)
	{
		holdAmmo--;
		allowShoot = false;
		mBodyAnimState = AnimState::SHOOT_ANIM;
		return true;
	}
	
	return false;
}

int Player::GetAmmo() const
{
	return holdAmmo;
}

void Player::Reload()
{
	holdAmmo = 18;
	mBodyAnimState = AnimState::RELOAD_ANIM;
}


void Player::Update(float delta_time)
{
	//Change animation based on state

	//body
	if (mBodyAnimState == AnimState::IDLE_ANIM)
	{
		mBodyAnim.Update(delta_time, 0, 0.1f, 0, 20);
		mPlayerRect.setTextureRect(*mBodyAnim.GetTextureRect());
	}
	else if(mBodyAnimState == AnimState::WALK_ANIM)
	{
		mBodyAnim.Update(delta_time, 1, 0.05f,0, 20);
		mPlayerRect.setTextureRect(*mBodyAnim.GetTextureRect());
	}
	else if(mBodyAnimState == AnimState::SHOOT_ANIM)
	{
		mBodyAnim.Update(delta_time, 2, 0.05f, 16, 18);
		mPlayerRect.setTextureRect(*mBodyAnim.GetTextureRect());
	}
	else if(mBodyAnimState == AnimState::RELOAD_ANIM)
	{
		mBodyAnim.Update(delta_time, 2, 0.05f,0, 15);
		mPlayerRect.setTextureRect(*mBodyAnim.GetTextureRect());
	}

	//feet
	if (mFeetAnimState == AnimState::IDLE_ANIM)
	{
		mFeetAnim.Hide();
		mPlayerFeetRect.setTextureRect(*mFeetAnim.GetTextureRect());
	}
	else if (mFeetAnimState == AnimState::WALK_ANIM)
	{
		mFeetAnim.Update(delta_time, 0, 0.05f,0, 20);
		mPlayerFeetRect.setTextureRect(*mFeetAnim.GetTextureRect());
	}

	//Set back
	mFeetAnimState = AnimState::IDLE_ANIM;

	if (!(mBodyAnimState == AnimState::SHOOT_ANIM || mBodyAnimState == AnimState::RELOAD_ANIM) || mBodyAnim.IsFinish())
		mBodyAnimState = AnimState::IDLE_ANIM;

	//Update player shoot cooldown
	elapsedShootTime += delta_time;
	if (elapsedShootTime >= shootCooldown && holdAmmo > 0)
	{
		allowShoot = true;
		elapsedShootTime = 0;
	}

	//death
	if (mHealth <= 0.0f)
	{
		mIsDead = true;
	}
}

void Player::LookAt(const sf::Vector2f& mouse_pos)
{
	const sf::Vector2f dir(mouse_pos.x - mPlayerRect.getPosition().x,
		mouse_pos.y - mPlayerRect.getPosition().y);
	
	mAngle = (atan2(dir.y, dir.x)) * 180 / static_cast<float>(M_PI);

	mDirVector = dir / sqrt(pow(dir.x, 2) + pow(dir.y, 2));

	mPlayerRect.setRotation(mAngle);
	mPlayerFeetRect.setRotation(mAngle);
}

void Player::SetPosition(const sf::Vector2f & pos)
{
	mPlayerRect.setPosition(pos);
	mPlayerFeetRect.setPosition(pos);
	mColliderBody.setPosition(pos);
	sf::Listener::setPosition(mPlayerRect.getPosition().x, 0, mPlayerRect.getPosition().y);
}

void Player::IncreaseHealth(int amount)
{
	mHealth += amount;
	if (mHealth > 200)
	{
		mHealth = 200;
	}
}

void Player::GetHit(int damage)
{
	mHealth -= damage;
	if (mHealth < 0)
	{
		mHealth = 0;
	}
	//TODO play blinking animation
}

sf::Vector2f Player::GetPosition() const
{
	return mPlayerRect.getPosition();
}

float Player::GetAngle() const
{
	return mAngle;
}

sf::Vector2f* Player::GetDirVect()
{
	return &mDirVector;
}

sf::RectangleShape* Player::GetFeetDraw()
{
	return &mPlayerFeetRect;
}
