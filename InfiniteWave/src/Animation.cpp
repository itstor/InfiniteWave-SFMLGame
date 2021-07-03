#include "Animation.h"

#include <SFML/Graphics/Transformable.hpp>
#include <cmath>
#include <SFML/Graphics/Text.hpp>

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
	mTotalFrame.x = mEnd.x - mStart.x;
	mTotalFrame.y = mEnd.y - mStart.y;

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
		const float maxTotalFrame = std::max(mTotalFrame.x, mTotalFrame.y);
		
		mRes = powf(0.01f, round(log10(maxTotalFrame)) - 1);
		mRes = mRes >= 1.0f ? 0.01f : mRes;
	}
	else if (mAnimType == AnimType::ZOOM)
	{
		mRes = powf(0.01f, round(log10(mTotalFrame.x)) - 1);
		mRes = mRes >= 1.0f ? 0.01f : mRes;
	}

	mTimePerFrame = time * mRes;
}

void Animation::Update(float deltaTime)
{
	mElapsedTime += deltaTime;

	if (mAnimType == AnimType::MOVE)
	{
		if (mElapsedTime >= mTimePerFrame)
		{
			const float posChangeY = mStart.y + mTotalFrame.y * mTransitionFunc(mProgress);
			const float posChangeX = mStart.x + mTotalFrame.x * mTransitionFunc(mProgress);

			mObject->setPosition(posChangeX, posChangeY);
			mProgress += mRes;

			mElapsedTime = 0.0f;

			if (mProgress >= 1.0f && !mBack || mProgress < 0.0f && mBack)
			{
				misFinished = true;
			}
			else if (mProgress >= 1.0f)
			{
				mRes *= -1;
			}
		}
	}
	else if (mAnimType == AnimType::ZOOM)
	{
		if (mElapsedTime >= mTimePerFrame)
		{
			const float scaleChangeX = mStart.x + mTotalFrame.x * mTransitionFunc(mProgress);

			mObject->setScale(scaleChangeX, scaleChangeX);
			mProgress += mRes;

			mElapsedTime = 0.0f;

			if (mProgress >= 1.0f && !mBack || mProgress < 0.0f && mBack)
			{
				misFinished = true;
			}
			else if (mProgress >= 1.0f)
			{
				mRes *= -1;
				mElapsedTime -= mBackDelay;
			}
		}
	}
}

bool Animation::IsFinished() const
{
	return misFinished;
}