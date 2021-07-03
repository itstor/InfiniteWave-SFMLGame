#pragma once
#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>


class Map : public sf::Drawable, public sf::Transformable
{
public:
	void Load(const std::string& map_file, sf::Vector2u tile_size, const int* tiles, unsigned width,
	          unsigned height);

private:
	sf::VertexArray mVertices;
	sf::Texture mTileSet;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
