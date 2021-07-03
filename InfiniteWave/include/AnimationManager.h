#pragma once
#ifndef ANIMATION_MANAGER_H_
#define ANIMATION_MANAGER_H_

#include <vector>
#include <SFML/System/Vector2.hpp>

#include "Animation.h"


class AnimationManager
{
public:
	AnimationManager() = default;
	~AnimationManager() = default;

	//To anim size set y properties to 0.0f
	void PlayAnimation(AnimType type, TransitionType transition_type, const sf::Vector2f& start, const sf::Vector2f& end, float time, sf::
	                   Transformable& object, bool back, float back_delay = 0.0f);

	void Update(float delta_time);
private:
	std::vector<Animation*> mAnimationContainer;
};

#endif