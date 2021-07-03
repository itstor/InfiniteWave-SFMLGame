#pragma once
#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <functional>
#include <SFML/System/Vector2.hpp>

namespace sf {
	class Color;
	class Drawable;
	class Transformable;
}


enum class AnimType { ZOOM, MOVE, OPACITY};
enum class TransitionType {LINEAR, EASE_IN_OUT_CUBIC, EASE_IN_OUT_BACK};

class Animation
{
public:
	Animation(AnimType anim_type, TransitionType transition_type, const sf::Vector2f& start, const sf::Vector2f& end, float time, sf::Transformable & object, bool back, float back_delay);
	~Animation() = default;

	void Update(float deltaTime);

	[[nodiscard]] bool IsFinished() const;

private:	
	bool misFinished = false;
	bool mBack = false;
	float mRes = 0.0;
	float mElapsedTime = 0.0f;
	float mProgress = 0.0f;
	float mTimePerFrame;
	float mBackDelay = 0.0f;

	AnimType mAnimType;
	sf::Vector2f mEnd;
	sf::Vector2f mStart;
	sf::Vector2f mTotalFrame;
	sf::Transformable* mObject;
	std::function<float(float)> mTransitionFunc;
};

#endif