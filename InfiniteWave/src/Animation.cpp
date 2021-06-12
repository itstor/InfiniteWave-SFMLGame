#include "Animation.h"


Animation::Animation() = default;


void Animation::Setup(sf::Texture* animTex, unsigned int imageCount, float time)
{
	this->imageCount = imageCount;
	this->time = time;

	uvRect.width = animTex->getSize().x / imageCount;
	uvRect.height = animTex->getSize().y;
}

void Animation::Update(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= time)
	{
		finish = false;
		totalTime -= time;
		currentImage++;
		
		if(currentImage >= imageCount)
		{
			finish = true;
			currentImage = 0;
		}
	}

	uvRect.left = currentImage * uvRect.width;
}

sf::IntRect* Animation::getTexture()
{
	return &uvRect;
}

void Animation::Reset()
{
	currentImage = 0;
}


bool Animation::isFinish() const
{
	return finish;
}


