#include "Grid.h"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

Grid::Grid(std::vector<Obstacle>& obstacle_container) :mObstacleContainer(obstacle_container){}

void Grid::Setup(const sf::Vector2f& grid_size, const sf::Vector2f& node_size)
{
	mGridSize = grid_size;
	mNodeSize = node_size;

	mNodeTotal.x = static_cast<int>(round(mGridSize.x / mNodeSize.x)); //Calculate x node total
	mNodeTotal.y = static_cast<int>(round(mGridSize.y / mNodeSize.y)); //Calculate y node total
}

void Grid::Draw(sf::RenderWindow* target)
{
	for (auto &grid:mGrid)
	{
		target->draw(*grid.getDraw());
	}
}

std::vector<Node>* Grid::getGrid()
{
	return &mGrid;
}

void Grid::CreateGrid()
{
	//std::cout << mObstacleContainer.size() << std::endl;
	for (int y = 0; y < mNodeTotal.y; y++)
	{
		for (int x = 0; x < mNodeTotal.x; x++)
		{
			bool walkable = true;
			for (auto &obs:mObstacleContainer)
			{
				sf::RectangleShape tempNode(mNodeSize);
				tempNode.setPosition(x*mNodeSize.x, y*mNodeSize.y);
				
				if (obs.onCollision(tempNode))
				{
					//std::cout << "Obstacle\n";
					mGrid.emplace_back(NodeType::OBSTACLE_NODE, sf::Vector2f(x*mNodeSize.x, y*mNodeSize.y), mNodeSize);
					walkable = false;
					break;
				}
			}
			if (walkable) mGrid.emplace_back(NodeType::WALKABLE_NODE, sf::Vector2f(x*mNodeSize.x, y*mNodeSize.y), mNodeSize);
		}
	}
}

void Grid::UpdatePlayerNode(sf::Vector2f player_position)
{
	float xLoc = player_position.x / mGridSize.x;
	float yLoc = player_position.y / mGridSize.y;
	
	xLoc = std::clamp(xLoc, 0.0f, 1.0f);
	yLoc = std::clamp(yLoc, 0.0f, 1.0f);

	int x = round((mNodeTotal.x - 1) * xLoc);
	int y = round((mNodeTotal.y - 1) * yLoc);

	const int vectIndex = y * mNodeTotal.x + x;

	if (vectIndex != mPrevStep)
	{
		mGrid[vectIndex].ChangeType(NodeType::PLAYER_NODE);
		mGrid[mPrevStep].ChangeType(NodeType::WALKABLE_NODE);
		mPrevStep = vectIndex;
	}
}

int Grid::GetGridIndexFromPosition(sf::Vector2f position) const
{
	float xLoc = position.x / mGridSize.x;
	float yLoc = position.y / mGridSize.y;
	
	xLoc = std::clamp(xLoc, 0.0f, 1.0f);
	yLoc = std::clamp(yLoc, 0.0f, 1.0f);

	int x = round((mNodeTotal.x - 1) * xLoc);
	int y = round((mNodeTotal.y - 1) * yLoc);

	return y * mNodeTotal.x + x;
}

NodeType Grid::GetNodeType(int index)
{
	return mGrid[index].GetType();
}

Node* Grid::GetNode(int index)
{
	return &mGrid[index];
}

