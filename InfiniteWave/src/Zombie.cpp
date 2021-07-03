#include "Zombie.h"

#include <iostream>
#include <utility>

Zombie::Zombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, sf::Texture& blood_tex, PathRequestManager& request_manager, sf::SoundBuffer& sound_buffer): mRequestManager(request_manager), mZombieSoundBuffer(sound_buffer), mZombieTex(zombie_tex), mBloodSplashTex(blood_tex)
{
	mColliderBody.setSize({288,311});
	mColliderBody.setOrigin(mColliderBody.getSize() * 0.5f);
	mEntityRect.setSize({ 288,311 });
	mEntityRect.setOrigin(mEntityRect.getSize() * 0.5f);

	//setup anim
	//TODO change texture to load from memory
	mEntityRect.setTexture(&mZombieTex);
	mZombieAnim.Setup(&mZombieTex, 2, 17);

	//setup blood
	mBloodRect.setTexture(&mBloodSplashTex);
	mBloodRect.setSize({200.0f,200.0f});
	mBloodRect.setOrigin(100.0f, 100.0f);
	mBloodAnim.Setup(&mBloodSplashTex, 1, 14);
	mBloodAnim.Hide();
	mBloodRect.setTextureRect(*mBloodAnim.GetTextureRect());

	//setup zombie sfx
	mZombieSound.setBuffer(mZombieSoundBuffer);
	mZombieSound.setLoop(false);
	mZombieSound.setPosition(mEntityRect.getPosition().x, 0, mEntityRect.getPosition().y);
	mZombieSound.setMinDistance(200.0f);
	mZombieSoundDelay = static_cast<float>(rand() % 8) + 7.0f;

	SetPosition(pos);
	
}

Zombie::~Zombie(){
	std::cout << "DEADDDDD\n";
};

void Zombie::Update(float delta_time, const sf::Vector2f& distance)
{
	if (!(mAnimState == AnimState::ATTACK_ANIM) || mZombieAnim.IsFinish())
		mAnimState = AnimState::WALK_ANIM;
	
	if (mAnimState == AnimState::WALK_ANIM)
	{
		mZombieAnim.Update(delta_time, 0, 0.05f, 0, 17);
		mEntityRect.setTextureRect(*mZombieAnim.GetTextureRect());
	}
	else if(mAnimState == AnimState::ATTACK_ANIM)
	{
		mZombieAnim.Update(delta_time, 1, 0.1f,0, 9);
		mEntityRect.setTextureRect(*mZombieAnim.GetTextureRect());
	}

	if (mShowBlood)
	{
		mBloodAnim.Update(delta_time, 0, 0.03f, 0,13);
		mBloodRect.setTextureRect(*mBloodAnim.GetTextureRect());
		if (mBloodAnim.IsFinish())
		{
			mShowBlood = false;
		}
	}

	mAttackCooldown -= delta_time;
	if (mAttackCooldown <= 0.0f)
	{
		mAllowAttack = true;
		mAttackCooldown = 5.0f;
	}

	//Update walk path every 2 second
	mPathUpdateDelay -= delta_time;
	if (mPathUpdateDelay <= 0.0f)
	{
		mRequestManager.AddRequest(*this, this->GetPosition());
		mPathUpdateDelay = 2.0f;
	}

	if (!mWalkPath.empty()) {
		mNextPosition = mWalkPath.top().GetNodePosition();
		LookAt(mNextPosition);
		//Check if zombie arrived to next point
		if (mRequestManager.GetGrid()->GetGridIndexFromPosition(mEntityRect.getPosition()) 
			== mRequestManager.GetGrid()->GetGridIndexFromPosition(mNextPosition))
		{
			mWalkPath.pop();
		}
	}

	mZombieSoundDelay -= delta_time;
	if (mZombieSoundDelay <= 0.0f)
	{
		mZombieSound.play();
		mZombieSoundDelay = static_cast<float>(rand() % 8) + 7.0f;
	}
	
}

void Zombie::SetPosition(const sf::Vector2f& position)
{
	mEntityRect.setPosition(position);
	mColliderBody.setPosition(position);
}

void Zombie::SetWalkPath(std::stack<Node> walk_path)
{
	mWalkPath = std::move(walk_path);
}

void Zombie::Move(float deltaTime)
{
		mMovePos = mDirVector * mMovementSpeed * deltaTime;
		mEntityRect.move(mMovePos);
		mColliderBody.move(mMovePos);
		mZombieSound.setPosition(mEntityRect.getPosition().x, 0, mEntityRect.getPosition().y); //Move sound source position
		mBloodRect.setPosition(mEntityRect.getPosition());
		mDirVector.x = 0.0f; mDirVector.y = 0.0f;
}

void Zombie::Attack()
{
	mAllowAttack = false;
	std::cout << "HRGHHH\n";
	mAnimState = AnimState::ATTACK_ANIM;
	//play attack anim
}

void Zombie::GetHit()
{
	mHealth -= 20;
	mShowBlood = true;
	std::cout << "ARGHH\n";
	if (mHealth <= 0)
	{
		std::cout << "DEAD AGAIN\n";
		mIsDead = true;
	}
}

bool Zombie::IsAllowAttack() const
{
	return mAllowAttack;
}

sf::Vector2f Zombie::GetPosition() const
{
	return mEntityRect.getPosition();
}

ZombieType Zombie::GetZombieType() const
{
	return mZombieType;
}

sf::RectangleShape* Zombie::GetBloodDraw()
{
	return &mBloodRect;
}

void Zombie::LookAt(const sf::Vector2f & target_position)
{
	const float PI = 3.14159265f;

	const sf::Vector2f dir(target_position.x - mEntityRect.getPosition().x,
		target_position.y - mEntityRect.getPosition().y);
	
	mAngle = (atan2(dir.y, dir.x)) * 180 / PI;

	mDirVector = dir / sqrt(pow(dir.x, 2) + pow(dir.y, 2));

	mEntityRect.setRotation(mAngle);
}