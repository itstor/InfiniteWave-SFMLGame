#pragma once
#include <queue>
#include <set>
#include <stack>
#include <unordered_set>

#include "Grid.h"

class PathFinding
{
public:
	PathFinding(Grid& grid);

	std::stack<Node> FindPath(sf::Vector2f start_position);
	Grid* getGrid();
private:
	//utils
	[[nodiscard]] bool isContains(const std::vector<Node>& node_container, const Node& node_to_check) const;
	[[nodiscard]] bool isContains(const std::unordered_set<Node, NodeHash>& node_container, const Node& node_to_check) const;
	[[nodiscard]] int GetDistance(const Node& nodeA, const Node& nodeB) const;
	
	Grid& mGrid;
};

