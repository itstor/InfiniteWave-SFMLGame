#pragma once
#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Image
{
public:
	Image();

	void Setup(const std::string& file_path, sf::Vector2f pos, float size_fact);
	void Setup(const std::string& file_path, sf::Vector2f pos, sf::Vector2f size);

	sf::RectangleShape* GetDraw();

private:
	sf::Texture mImageTex;
	sf::RectangleShape mImageRect;
};

#endif