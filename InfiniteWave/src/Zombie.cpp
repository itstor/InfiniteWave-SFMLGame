#include "Zombie.h"

#include <iostream>
#include <utility>

Zombie::Zombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, sf::Texture& blood_tex, PathRequestManager& request_manager, sf::SoundBuffer& sound_buffer): mRequestManager(request_manager), mZombieSoundBuffer(sound_buffer), zombieTex(zombie_tex), bloodSplashTex(blood_tex)
{
	ColliderBody.setSize({288,311});
	ColliderBody.setOrigin(ColliderBody.getSize() * 0.5f);
	entityRect.setSize({ 288,311 });
	entityRect.setOrigin(entityRect.getSize() * 0.5f);

	//setup anim
	//TODO change texture to load from memory
	entityRect.setTexture(&zombieTex);
	zombieAnim.Setup(&zombieTex, 2, 17);

	//setup blood
	bloodRect.setTexture(&bloodSplashTex);
	bloodRect.setSize({200.0f,200.0f});
	bloodRect.setOrigin(100.0f, 100.0f);
	bloodAnim.Setup(&bloodSplashTex, 1, 14);
	bloodAnim.Hide();
	bloodRect.setTextureRect(*bloodAnim.getTexture());

	//setup zombie sfx
	mZombieSound.setBuffer(mZombieSoundBuffer);
	mZombieSound.setLoop(false);
	mZombieSound.setPosition(entityRect.getPosition().x, 0, entityRect.getPosition().y);
	mZombieSound.setMinDistance(200.0f);
	zombieSoundDelay = static_cast<float>(rand() % 8) + 7.0f;

	setPosition(pos);
	
}

Zombie::~Zombie(){
	std::cout << "DEADDDDD\n";
};

void Zombie::Update(float deltaTime, const sf::Vector2f& distance)
{
	if (!(animState == AnimState::ATTACK_ANIM) || zombieAnim.isFinish())
		animState = AnimState::WALK_ANIM;
	
	if (animState == AnimState::WALK_ANIM)
	{
		zombieAnim.Update(deltaTime, 0, 0.05f, 0, 17);
		entityRect.setTextureRect(*zombieAnim.getTexture());
	}
	else if(animState == AnimState::ATTACK_ANIM)
	{
		zombieAnim.Update(deltaTime, 1, 0.1f,0, 9);
		entityRect.setTextureRect(*zombieAnim.getTexture());
	}

	if (showBlood)
	{
		bloodAnim.Update(deltaTime, 0, 0.03f, 0,13);
		bloodRect.setTextureRect(*bloodAnim.getTexture());
		if (bloodAnim.isFinish())
		{
			showBlood = false;
		}
	}

	attackCooldown -= deltaTime;
	if (attackCooldown <= 0.0f)
	{
		allowAttack = true;
		attackCooldown = 5.0f;
	}

	//Update walk path every 2 second
	pathUpdateDelay -= deltaTime;
	if (pathUpdateDelay <= 0.0f)
	{
		mRequestManager.AddRequest(*this, this->getPosition());
		pathUpdateDelay = 2.0f;
	}

	if (!mWalkPath.empty()) {
		nextPosition = mWalkPath.top().GetNodePosition();
		lookAt(nextPosition);
		//Check if zombie arrived to next point
		if (mRequestManager.getGrid()->GetGridIndexFromPosition(entityRect.getPosition()) 
			== mRequestManager.getGrid()->GetGridIndexFromPosition(nextPosition))
		{
			mWalkPath.pop();
		}
	}

	zombieSoundDelay -= deltaTime;
	if (zombieSoundDelay <= 0.0f)
	{
		mZombieSound.play();
		zombieSoundDelay = static_cast<float>(rand() % 8) + 7.0f;
	}
	
}

void Zombie::setPosition(const sf::Vector2f& pos)
{
	entityRect.setPosition(pos);
	ColliderBody.setPosition(pos);
}

void Zombie::setWalkPath(std::stack<Node> walk_path)
{
	mWalkPath = std::move(walk_path);
}

void Zombie::Move(float deltaTime)
{
		movePos = mDirVect * movementSpeed * deltaTime;
		entityRect.move(movePos);
		ColliderBody.move(movePos);
		mZombieSound.setPosition(entityRect.getPosition().x, 0, entityRect.getPosition().y); //Move sound source position
		bloodRect.setPosition(entityRect.getPosition());
		mDirVect.x = 0.0f; mDirVect.y = 0.0f;
}

void Zombie::Attack()
{
	allowAttack = false;
	std::cout << "HRGHHH\n";
	animState = AnimState::ATTACK_ANIM;
	//play attack anim
}

void Zombie::getHit()
{
	health -= 20;
	showBlood = true;
	std::cout << "ARGHH\n";
	if (health <= 0)
	{
		std::cout << "DEAD AGAIN\n";
		misDead = true;
	}
}

bool Zombie::isAllowAttack() const
{
	return allowAttack;
}

sf::Vector2f Zombie::getPosition() const
{
	return entityRect.getPosition();
}

ZombieType Zombie::getZombieType() const
{
	return mZombieType;
}

sf::RectangleShape* Zombie::getBloodDraw()
{
	return &bloodRect;
}

void Zombie::lookAt(const sf::Vector2f & target_position)
{
	const float PI = 3.14159265f;

	const sf::Vector2f dir(target_position.x - entityRect.getPosition().x,
		target_position.y - entityRect.getPosition().y);
	
	angle = (atan2(dir.y, dir.x)) * 180 / PI;

	mDirVect = dir / sqrt(pow(dir.x, 2) + pow(dir.y, 2));

	entityRect.setRotation(angle);
}