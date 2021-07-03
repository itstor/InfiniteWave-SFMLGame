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
		target->draw(*grid.GetDraw());
	}
}

std::vector<Node>* Grid::GetGrid()
{
	return &mGrid;
}

std::vector<Node> Grid::GetNeighbors(const Node & node)
{
	std::vector<Node> neighbors;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
			{
				continue;
			}

			const int checkX = node.GetGridIndex().x + i;
			const int checkY = node.GetGridIndex().y + j;

			if (checkX >= 0 && checkX < mNodeTotal.x && checkY >= 0 &&checkY < mNodeTotal.y)
			{
				neighbors.push_back(mGrid[checkY * mNodeTotal.x + checkX]);
			}
		}	
	}
	return neighbors;
}

void Grid::CreateGrid()
{
	//std::cout << mObstacleContainer.size() << std::endl;
	int id = 0;
	for (int y = 0; y < mNodeTotal.y; y++)
	{
		for (int x = 0; x < mNodeTotal.x; x++)
		{
			bool walkable = true;
			for (auto &obs:mObstacleContainer)
			{
				sf::RectangleShape tempNode(mNodeSize);
				tempNode.setPosition(x*mNodeSize.x, y*mNodeSize.y);
				
				if (obs.OnCollision(tempNode))
				{
					//std::cout << "Obstacle\n";
					mGrid.emplace_back(NodeType::OBSTACLE_NODE, sf::Vector2f(x*mNodeSize.x, y*mNodeSize.y), mNodeSize, sf::Vector2i(x, y), id++);
					walkable = false;
					break;
				}
			}
			if (walkable) mGrid.emplace_back(NodeType::WALKABLE_NODE, sf::Vector2f(x*mNodeSize.x, y*mNodeSize.y), mNodeSize, sf::Vector2i(x, y), id++);
		}
	}
}

void Grid::UpdatePlayerNode(const sf::Vector2f& player_position)
{
	if (const int vectIndex = GetGridIndexFromPosition(player_position); vectIndex != mPrevIndexPlayerNode)
	{
		mGrid[vectIndex].ChangeType(NodeType::PLAYER_NODE);
		mGrid[mPrevIndexPlayerNode].ChangeType(NodeType::WALKABLE_NODE);
		mPrevIndexPlayerNode = vectIndex;
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

int Grid::GetPlayerIndexNode() const
{
	return mPrevIndexPlayerNode;
}

NodeType Grid::GetNodeType(int index)
{
	return mGrid[index].GetType();
}

Node* Grid::GetNode(int index)
{
	return &mGrid[index];
}

