#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Animation.h"

class AnimationManager
{
public:
	AnimationManager() = default;
	~AnimationManager() = default;

	//To anim size set y properties to 0.0f
	void playAnimation(AnimType type, const sf::Vector2f& start, const sf::Vector2f& end, float time, sf::Transformable& object, bool back, float
	                   back_delay = 0.0f);

	void Update(float deltaTime);
private:
	std::vector<Animation*> animationContainer;
};

