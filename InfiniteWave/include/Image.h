#pragma once
#include <string>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

class Image
{
public:
	Image();

	void Setup(const std::string& file_path, sf::Vector2f pos, float size_fact);

	sf::RectangleShape* getDraw();
private:
	sf::Texture imgTexture;
	sf::RectangleShape img;
};

