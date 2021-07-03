#include "SpriteAnimation.h"

#include <iostream>


SpriteAnimation::SpriteAnimation() = default;


void SpriteAnimation::Setup(sf::Texture* anim_tex, unsigned int row, unsigned int max_image_count)
{
	mMaxImage = max_image_count;
	mUVRect.width = anim_tex->getSize().x / max_image_count;
	mUVRect.height = anim_tex->getSize().y / row;
}

void SpriteAnimation::Update(float delta_time, int row, float switch_time, unsigned int start_frame, unsigned int end_frame)
{
	//Reset current frame to start frame
	if (row != mPrevRow)
	{
		mPrevRow = row;
		mTotalTime = 0;
		mCurrentImage = 0 + start_frame;
	}
	
	mTotalTime += delta_time;
	if (mTotalTime >= switch_time)
	{
		mFinish = false;
		mTotalTime = 0;
		mCurrentImage++;

		if (mCurrentImage >= end_frame)
		{
			mFinish = true;
			mCurrentImage = 0;
		}
	}

	mUVRect.left = mCurrentImage * mUVRect.width;
	mUVRect.top = row * mUVRect.height;
}

void SpriteAnimation::Hide()
{
	mUVRect.left = (mMaxImage + 1) * mUVRect.width;
}

sf::IntRect* SpriteAnimation::GetTextureRect()
{
	return &mUVRect;
}


bool SpriteAnimation::IsFinish() const
{
	return mFinish;
}


