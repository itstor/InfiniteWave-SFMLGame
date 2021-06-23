#pragma once
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
	void UpdatePlayerNode(sf::Vector2f player_position);
	[[nodiscard]] int GetGridIndexFromPosition(sf::Vector2f position) const;
	NodeType GetNodeType(int index);

	Node * GetNode(int index);

	void Draw(sf::RenderWindow* target);
	std::vector<Node>* getGrid();
private:
	
	std::vector<Node> mGrid;
	std::vector<Obstacle> &mObstacleContainer;
	
	sf::Vector2f mGridSize;
	sf::Vector2f mNodeSize;
	sf::Vector2i mNodeTotal;

	int mPrevStep;
};

