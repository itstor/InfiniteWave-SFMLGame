#include "Image.h"

Image::Image() = default;

void Image::Setup(const std::string& file_path, sf::Vector2f pos, float size_fact)
{
	imgTexture.loadFromFile(file_path);

	img.setTexture(&imgTexture);
	img.setSize(sf::Vector2f(static_cast<float>(imgTexture.getSize().x), static_cast<float>(imgTexture.getSize().y)));
	img.setScale(size_fact, size_fact);
	img.setPosition(pos);
}

sf::RectangleShape* Image::getDraw()
{
	return &img;
}
