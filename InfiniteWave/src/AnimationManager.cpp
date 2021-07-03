#include "AnimationManager.h"
#include <SFML/System/Vector2.hpp>

void AnimationManager::PlayAnimation(AnimType type, TransitionType transition_type, const sf::Vector2f& start,
                                     const sf::Vector2f& end, float time, sf::Transformable& object, bool back,
                                     float back_delay)
{
	mAnimationContainer.push_back(new Animation(type, transition_type, start, end, time, object, back, back_delay));
}

void AnimationManager::Update(float delta_time)
{
	if (!mAnimationContainer.empty())
	{
		for (size_t i = 0; i < mAnimationContainer.size(); i++)
		{
			mAnimationContainer[i]->Update(delta_time);
			if (mAnimationContainer[i]->IsFinished())
			{
				delete mAnimationContainer[i];
				mAnimationContainer.erase(mAnimationContainer.begin() + i);
			}
		}
	}
}


