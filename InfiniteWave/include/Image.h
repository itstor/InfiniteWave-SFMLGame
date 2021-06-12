#pragma once
#include <string>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

class Image
{
public:
	Image();

	void Setup(const std::string& file_path, sf::Vector2f pos, float size_fact);
	void Setup(const std::string& file_path, sf::Vector2f pos, sf::Vector2f size);

	sf::RectangleShape* getDraw();
private:
	sf::Texture imgTexture;
	sf::RectangleShape img;
};

