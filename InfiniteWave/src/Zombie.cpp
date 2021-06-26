#include "Zombie.h"

#include <iostream>
#include <utility>

Zombie::Zombie(const sf::Vector2f& pos, sf::Texture& zombie_tex, PathRequestManager& request_manager): mRequestManager(request_manager), zombieTex(zombie_tex)
{
	ColliderBody.setSize({288,311});
	ColliderBody.setOrigin(ColliderBody.getSize() * 0.5f);
	entityRect.setSize({ 288,311 });
	entityRect.setOrigin(entityRect.getSize() * 0.5f);

	//setup anim
	//TODO change texture to load from memory
	entityRect.setTexture(&zombieTex);
	zombieAnim.Setup(&zombieTex, 2, 17);

	setPosition(pos);
}

Zombie::~Zombie(){
	std::cout << "DEADDDDD\n";
};

void Zombie::Update(float deltaTime, const sf::Vector2f& distance)
{
	if (!(animState == ATTACK_ANIM) || zombieAnim.isFinish())
		animState = WALK_ANIM;
	
	if (animState == WALK_ANIM)
	{
		zombieAnim.Update(deltaTime, 0, 0.05f, 0, 17);
		entityRect.setTextureRect(*zombieAnim.getTexture());
	}
	else if(animState == ATTACK_ANIM)
	{
		zombieAnim.Update(deltaTime, 1, 0.1f,0, 9);
		entityRect.setTextureRect(*zombieAnim.getTexture());
	}

	attackElapsedTime += deltaTime;
	if (attackElapsedTime >= attackCooldown)
	{
		allowAttack = true;
		attackElapsedTime = 0;
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
		movePos.x = 0.0f; movePos.y = 0.0f;
}

void Zombie::Attack()
{
	allowAttack = false;
	std::cout << "HRGHHH\n";
	animState = ATTACK_ANIM;
	//play attack anim
}

void Zombie::getHit()
{
	health -= 20;
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

void Zombie::lookAt(const sf::Vector2f & target_position)
{
	const float PI = 3.14159265f;

	const sf::Vector2f dir(target_position.x - entityRect.getPosition().x,
		target_position.y - entityRect.getPosition().y);
	
	angle = (atan2(dir.y, dir.x)) * 180 / PI;

	mDirVect = dir / sqrt(pow(dir.x, 2) + pow(dir.y, 2));

	entityRect.setRotation(angle);
}


