#include "PathFinding.h"

#include <deque>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_set>

PathFinding::PathFinding(Grid& grid): mGrid(grid)
{
}

std::stack<Node> PathFinding::FindPath(sf::Vector2f start_position)
{
	//sf::Clock clock;
	const Node startNode = *mGrid.GetNode(mGrid.GetGridIndexFromPosition(start_position));
	const Node targetNode = *mGrid.GetNode(mGrid.GetPlayerIndexNode());

	std::vector<Node> openSet;
	std::unordered_set<Node, NodeHash> closedSet;

	openSet.push_back(startNode);
	std::push_heap(openSet.begin(), openSet.end(), std::greater<>{});
	
	if (startNode.GetType() == NodeType::WALKABLE_NODE) {
		while (!openSet.empty())
		{
			Node currentNode = openSet.front();
			std::pop_heap(openSet.begin(), openSet.end(), std::greater<>{});
			openSet.pop_back();
			closedSet.insert(currentNode);

			if (currentNode == targetNode) {
				///std::cout << currentNode.GetGridIndex().x << " " << currentNode.GetGridIndex().y << std::endl;
				//std::cout << clock.getElapsedTime().asSeconds() << std::endl;
				
				//create walk path
				openSet.push_back(currentNode);
				std::stack<Node> walkPath;
				for (const auto& node : openSet)
				{
					if (node == targetNode)
					{
						currentNode = node;
						break;
					}
				}

				while (currentNode != startNode)
				{
					walkPath.push(currentNode);
					currentNode = *currentNode.GetParent();
				}
				
				return walkPath;
			}

			for (auto &neighbor : mGrid.GetNeighbors(currentNode))
			{
				if (neighbor.GetType() == NodeType::OBSTACLE_NODE || isContains(closedSet, neighbor))
				{
					continue;
				}

				if (const int movementCostToNeighbor = currentNode.GetgCost() + GetDistance(currentNode, neighbor);
					movementCostToNeighbor < neighbor.GetgCost() || !isContains(openSet, neighbor))
				{
					neighbor.SetgCost(movementCostToNeighbor);
					neighbor.SethCost(GetDistance(neighbor, targetNode));
					neighbor.setNodeParent(&currentNode);

					if (!isContains(openSet, neighbor))
					{
						openSet.push_back(neighbor);
						std::push_heap(openSet.begin(), openSet.end(), std::greater<>{});
					}

				}
			}
		}
	}
}

Grid * PathFinding::getGrid()
{
	return &mGrid;
}

bool PathFinding::isContains(const std::vector<Node>& node_container, const Node & node_to_check) const
{
	if (std::find(node_container.begin(), node_container.end(), node_to_check) != node_container.end())
	{
		return true;
	}
	return false;
	
}

bool PathFinding::isContains(const std::unordered_set<Node, NodeHash>& node_container, const Node & node_to_check) const
{
	if (node_container.find(node_to_check) != node_container.end())
	{
		return true;
	}
	return false;
}

int PathFinding::GetDistance(const Node & nodeA, const Node & nodeB) const
{
	const int distanceX = abs(nodeA.GetGridIndex().x - nodeB.GetGridIndex().x);
	const int distanceY = abs(nodeA.GetGridIndex().y - nodeB.GetGridIndex().y);

	if (distanceX > distanceY)
	{
		return 14 * distanceY + 10 * (distanceX - distanceY);
	}
	return 14 * distanceX + 10 * (distanceY - distanceX);
}
