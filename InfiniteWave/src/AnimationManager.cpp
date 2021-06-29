#include "AnimationManager.h"
#include <SFML/System/Vector2.hpp>

void AnimationManager::playAnimation(AnimType type, const sf::Vector2f& start, const sf::Vector2f& end, float time, sf::Transformable & object, bool back, float back_delay)
{
	animationContainer.push_back(new Animation(type, start, end, time, object, back, back_delay));
}

void AnimationManager::Update(float deltaTime)
{
	if (!animationContainer.empty())
	{
		for (auto &animation:animationContainer)
		{
			animation->Update(deltaTime);
			if (animation->isFinished())
			{
				animationContainer.erase(std::find(animationContainer.begin(), animationContainer.end(), animation));
			}
		}
	}
}


