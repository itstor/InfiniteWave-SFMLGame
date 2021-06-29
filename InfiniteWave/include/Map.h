#pragma once
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

class Map : public sf::Drawable, public sf::Transformable
{
public:
	void load(const std::string& mapFile, sf::Vector2u tileSize, const int* tiles, unsigned int width,
	          unsigned int height);
private:
	sf::VertexArray vertices;
	sf::Texture tileSet;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

