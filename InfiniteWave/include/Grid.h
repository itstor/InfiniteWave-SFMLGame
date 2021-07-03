#pragma once
#ifndef GRID_H_
#define GRID_H_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "Node.h"
#include "Obstacle.h"


class Grid
{
public:
	Grid(std::vector<Obstacle>& obstacle_container);

	void Setup(const sf::Vector2f& grid_size, const sf::Vector2f& node_size);
	void CreateGrid();
	void UpdatePlayerNode(const sf::Vector2f& player_position);
	void Draw(sf::RenderWindow* target);
	
	[[nodiscard]] int GetGridIndexFromPosition(sf::Vector2f position) const;
	[[nodiscard]] int GetPlayerIndexNode() const;
	NodeType GetNodeType(int index);
	Node * GetNode(int index);
	std::vector<Node>* GetGrid();
	std::vector<Node> GetNeighbors(const Node& node);

private:
	int mPrevIndexPlayerNode;

	sf::Vector2f mGridSize;
	sf::Vector2f mNodeSize;
	sf::Vector2i mNodeTotal;

	std::vector<Node> mGrid;
	std::vector<Obstacle> &mObstacleContainer;
};

#endif

