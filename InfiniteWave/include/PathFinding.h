#pragma once
#ifndef PATH_FINDING_H_
#define PATH_FINDING_H_

#include <stack>
#include <unordered_set>

#include "Grid.h"


class PathFinding
{
public:
	PathFinding(Grid& grid);

	std::stack<Node> FindPath(sf::Vector2f start_position);
	
	Grid* GetGrid();
private:
	//utils
	[[nodiscard]] bool IsContains(const std::vector<Node>& node_container, const Node& node_to_check) const;
	[[nodiscard]] bool IsContains(const std::unordered_set<Node, NodeHash>& node_container, const Node& node_to_check) const;
	[[nodiscard]] int GetDistance(const Node& nodeA, const Node& nodeB) const;
	
	Grid& mGrid;
};

#endif

