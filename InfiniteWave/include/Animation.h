#pragma once
#include <SFML/Graphics/Texture.hpp>

class Animation
{
public:
	Animation();

	void Setup(const std::string& file_path, unsigned int imageCount, float time);
	void Update(float deltaTime);
	void Reset();
	
	[[nodiscard]] bool isFinish() const;
private:
	sf::Texture animTex;
	sf::IntRect uvRect;
	
	unsigned int imageCount;
	unsigned int currentImage;
	bool finish;
	float totalTime = 0.0f;
	float time;
};

