#include "Image.h"
#include "Config.h"

Image::Image() = default;

void Image::Setup(const std::string& file_path, sf::Vector2f pos, float size_fact)
{
	imgTexture.loadFromFile(file_path);
	imgTexture.setSmooth(true);
	const sf::Vector2f size(imgTexture.getSize().x, imgTexture.getSize().y);
	
	img.setTexture(&imgTexture);

	img.setSize(size);
	img.setScale(size_fact, size_fact);

	img.setOrigin(size.x/2, size.y/2);
	img.setPosition(pos);
}


void Image::Setup(const std::string& file_path, sf::Vector2f pos, sf::Vector2f size)
{
	imgTexture.loadFromFile(file_path);
	imgTexture.setSmooth(true);
	
	img.setTexture(&imgTexture);

	img.setSize(size);

	img.setOrigin(size.x / 2, size.y / 2);
	img.setPosition(pos);
}

sf::RectangleShape* Image::getDraw()
{
	return &img;
}
