#include "Animation.h"

#include <SFML/Graphics/Transformable.hpp>
#include <cmath>
#include <utility>

Animation::Animation(AnimType anim_type, TransitionType transition_type, const sf::Vector2f& start,
                     const sf::Vector2f& end, float time, sf::Transformable& object, bool back = false,
                     float back_delay = 0.0f): mObject(nullptr)
{
	mAnimType = anim_type;
	mStart = start;
	mEnd = end;
	mBack = back;
	mObject = &object;
	mBackDelay = back_delay;
	totalFrame.x = mEnd.x - mStart.x;
	totalFrame.y = mEnd.y - mStart.y;

	switch (transition_type)
	{
	case TransitionType::LINEAR: mTransitionFunc = [](float x) {return x; }; break; //Linear
	case TransitionType::EASE_IN_OUT_CUBIC: mTransitionFunc = [](float x)
		{
			return x < 0.5 ? 4 * pow(x, 3) : 1 - pow(-2 * x + 2, 3) / 2;
		};
		break; //easeinoutcubic
	case TransitionType::EASE_IN_OUT_BACK: mTransitionFunc = [](float x)
	{
		const float c1 = 1.70158f;
		const float c2 = c1 * 1.525f;

		return x < 0.5
		  ? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
		  : (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
	}; break;
	default: break;
	}
	
	//calculate progress increment
	if (mAnimType == AnimType::MOVE)
	{
		const float maxTotalFrame = std::max(totalFrame.x, totalFrame.y);
		res = powf(0.1f, round(log10(maxTotalFrame)) - 1);
		res = res >= 1.0f ? 0.1f : res;
	}
	else if (mAnimType == AnimType::ZOOM)
	{
		res = powf(0.01f, round(log10(totalFrame.x)) - 1);
		res = res >= 1.0f ? 0.01f : res;
	}

	timePerFrame = time * res;
}

void Animation::Update(float deltaTime)
{
	elapsedTime += deltaTime;

	if (mAnimType == AnimType::MOVE)
	{
		if (elapsedTime >= timePerFrame)
		{
			const float posChangeY = mStart.y + totalFrame.y * mTransitionFunc(progress);
			const float posChangeX = mStart.x + totalFrame.x * mTransitionFunc(progress);

			mObject->setPosition(posChangeX, posChangeY);
			progress += res;

			elapsedTime = 0.0f;

			if (progress >= 1.0f && !mBack || progress < 0.0f && mBack)
			{
				misFinished = true;
			}
			else if (progress >= 1.0f)
			{
				res *= -1;
			}
		}
	}
	else if (mAnimType == AnimType::ZOOM)
	{
		if (elapsedTime >= timePerFrame)
		{
			const float scaleChangeX = mStart.x + totalFrame.x * mTransitionFunc(progress);

			mObject->setScale(scaleChangeX, scaleChangeX);
			progress += res;

			elapsedTime = 0.0f;

			if (progress >= 1.0f && !mBack || progress < 0.0f && mBack)
			{
				misFinished = true;
			}
			else if (progress >= 1.0f)
			{
				res *= -1;
				elapsedTime -= mBackDelay;
			}
		}
	}
}

bool Animation::isFinished() const
{
	return misFinished;
}