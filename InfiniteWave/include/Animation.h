#pragma once
#include <SFML/Graphics/Texture.hpp>

class Animation
{
public:
	Animation();

	void Setup(sf::Texture* animTex, unsigned row, unsigned maxImageCount);
	void Update(float deltaTime, int row, float switchTime, unsigned endFrame, unsigned startFrame = 0, bool pause = false);
	void Hide();
	sf::IntRect* getTexture();
	void Reset();
	
	[[nodiscard]] bool isFinish() const;
	sf::IntRect uvRect;
	
private:
	unsigned int currentImage = 0;
	unsigned int maxImage = 0;
	int prevRow = -1;
	bool finish = false;
	float totalTime = 0.0f;
	
};

