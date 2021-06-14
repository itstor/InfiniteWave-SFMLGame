#pragma once
#include <SFML/Graphics/Texture.hpp>

class Animation
{
public:
	Animation();

	void Setup(sf::Texture* animTex, unsigned imageCount, float time);
	void Update(float deltaTime);
	sf::IntRect* getTexture();
	void Reset();
	
	[[nodiscard]] bool isFinish() const;
	sf::IntRect uvRect;
	
private:
	sf::Texture animTex;
	
	unsigned int imageCount = 0;
	unsigned int currentImage = 0;
	bool finish = false;
	float totalTime = 0.0f;
	float time = 0.0f;
};

