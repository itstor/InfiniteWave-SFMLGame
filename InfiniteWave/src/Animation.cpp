#include "Animation.h"


void Animation::Setup(const std::string& file_path, unsigned int imageCount, float time)
{
	animTex.loadFromFile(file_path);
	animTex.setSmooth(true);
	this->imageCount = imageCount;
	this->time = time;

	uvRect.width = animTex.getSize().x / imageCount;
	uvRect.height = animTex.getSize().y;
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

void Animation::Reset()
{
	currentImage = 0;
}


bool Animation::isFinish() const
{
	return finish;
}


