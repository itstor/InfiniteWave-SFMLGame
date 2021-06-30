#include "AnimationManager.h"
#include <SFML/System/Vector2.hpp>

void AnimationManager::playAnimation(AnimType type, TransitionType transition_type, const sf::Vector2f& start,
                                     const sf::Vector2f& end, float time, sf::Transformable& object, bool back,
                                     float back_delay)
{
	animationContainer.push_back(new Animation(type, transition_type, start, end, time, object, back, back_delay));
}

void AnimationManager::Update(float deltaTime)
{
	if (!animationContainer.empty())
	{
		for (size_t i = 0; i < animationContainer.size(); i++)
		{
			animationContainer[i]->Update(deltaTime);
			if (animationContainer[i]->isFinished())
			{
				delete animationContainer[i];
				animationContainer.erase(animationContainer.begin() + i);
			}
		}
	}
}


