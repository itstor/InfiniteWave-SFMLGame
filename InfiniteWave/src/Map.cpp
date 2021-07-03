#include "Map.h"

#include <SFML/Graphics/RenderTarget.hpp>

void Map::Load(const std::string& map_file, sf::Vector2u tile_size, const int* tiles, unsigned int width, unsigned int height)
{
	mTileSet.loadFromFile(map_file);

	mVertices.setPrimitiveType(sf::Quads);
	mVertices.resize(width * height * 4);

	for (unsigned int i = 0; i < width; i++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			const int tileNumber = tiles[i + j * width];

			int tu = tileNumber % (mTileSet.getSize().x / tile_size.x);
			int tv = tileNumber / (mTileSet.getSize().x / tile_size.x);

			sf::Vertex* quad = &mVertices[(i + j * width) * 4];

			quad[0].position = sf::Vector2f(i * tile_size.x, j * tile_size.y);
			quad[1].position = sf::Vector2f((i + 1) * tile_size.x, j * tile_size.y);
			quad[2].position = sf::Vector2f((i + 1) * tile_size.x, (j + 1) * tile_size.y);
			quad[3].position = sf::Vector2f(i * tile_size.x, (j + 1) * tile_size.y);

			quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
			quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
		}
	}
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = &mTileSet;

	target.draw(mVertices, states);
}
