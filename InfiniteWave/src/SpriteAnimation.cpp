#include "SpriteAnimation.h"

#include <iostream>


SpriteAnimation::SpriteAnimation() = default;


void SpriteAnimation::Setup(sf::Texture* animTex, unsigned int row, unsigned int maxImageCount)
{
	maxImage = maxImageCount;
	uvRect.width = animTex->getSize().x / maxImageCount;
	uvRect.height = animTex->getSize().y / row;
}

void SpriteAnimation::Update(float deltaTime, int row, float switchTime, unsigned int startFrame, unsigned int endFrame)
{
	//Reset current frame to start frame
	if (row != prevRow)
	{
		prevRow = row;
		totalTime = 0;
		currentImage = 0 + startFrame;
	}
	
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		finish = false;
		totalTime = 0;
		currentImage++;

		if (currentImage >= endFrame)
		{
			finish = true;
			currentImage = 0;
		}
	}

	uvRect.left = currentImage * uvRect.width;
	uvRect.top = row * uvRect.height;
}

void SpriteAnimation::Hide()
{
	uvRect.left = (maxImage + 1) * uvRect.width;
}

sf::IntRect* SpriteAnimation::getTexture()
{
	return &uvRect;
}


bool SpriteAnimation::isFinish() const
{
	return finish;
}


