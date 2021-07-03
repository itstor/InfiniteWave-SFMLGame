#include "Image.h"
#include "Config.h"

Image::Image() = default;

void Image::Setup(const std::string& file_path, sf::Vector2f pos, float size_fact)
{
	mImageTex.loadFromFile(file_path);
	mImageTex.setSmooth(true);
	const sf::Vector2f size(mImageTex.getSize().x, mImageTex.getSize().y);
	
	mImageRect.setTexture(&mImageTex);

	mImageRect.setSize(size);
	mImageRect.setScale(size_fact, size_fact);

	mImageRect.setOrigin(size.x/2, size.y/2);
	mImageRect.setPosition(pos);
}


void Image::Setup(const std::string& file_path, sf::Vector2f pos, sf::Vector2f size)
{
	mImageTex.loadFromFile(file_path);
	mImageTex.setSmooth(true);
	
	mImageRect.setTexture(&mImageTex);

	mImageRect.setSize(size);

	mImageRect.setOrigin(size.x / 2, size.y / 2);
	mImageRect.setPosition(pos);
}

sf::RectangleShape* Image::GetDraw()
{
	return &mImageRect;
}
