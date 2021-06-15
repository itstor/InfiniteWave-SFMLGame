#include "Animation.h"

#include <iostream>


Animation::Animation() = default;


void Animation::Setup(sf::Texture* animTex, unsigned int row, unsigned int maxImageCount)
{
	maxImage = maxImageCount;
	uvRect.width = animTex->getSize().x / maxImageCount;
	uvRect.height = animTex->getSize().y / row;
}

void Animation::Update(float deltaTime, int row, float switchTime, unsigned int endFrame, unsigned int startFrame, bool pause)
{
	if (row != prevRow || pause)
	{
		prevRow = row;
		totalTime = 0;
		currentImage = 0 + startFrame;
	}
	
	if (!pause) {
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
	}

	uvRect.left = currentImage * uvRect.width;
	uvRect.top = row * uvRect.height;
}

void Animation::Hide()
{
	uvRect.left = (maxImage + 1) * uvRect.width;
}

sf::IntRect* Animation::getTexture()
{
	return &uvRect;
}


bool Animation::isFinish() const
{
	return finish;
}


