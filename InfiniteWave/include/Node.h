#pragma once
#ifndef NODE_H_
#define NODE_H_

#include <SFML/Graphics/RectangleShape.hpp>

enum class NodeType {WALKABLE_NODE, OBSTACLE_NODE, PLAYER_NODE};

class Node
{
public:
	Node(NodeType node_type, const sf::Vector2f& node_position, const sf::Vector2f& node_size, const sf::Vector2i& grid_index, int id);

	bool operator==(const Node& node) const;
	bool operator!=(const Node& node) const;
	bool operator<(const Node& node) const;
	bool operator>(const Node& node) const;
	
	void ChangeType(NodeType node_type);
	
	//getter setter
	void SetNodeParent(Node* node);
	void SetGCost(int g_cost);
	void SetHCost(int h_cost);
	int GetGCost() const;
	int GetHCost() const;
	int GetFCost() const;
	int GetNodeId() const;
	Node* GetParent() const;
	sf::Vector2i GetGridIndex() const;
	sf::Vector2f GetNodePosition(bool center = true) const;
	
	sf::RectangleShape* GetDraw();
	NodeType GetType() const;
private:
	int mNodeId = 0;
	int mGCost = 0;
	int mHCost = 0;

	sf::RectangleShape mNodeRect;
	sf::Vector2i mGridIndex;
	sf::Vector2f mNodePostion;
	sf::Vector2f mNodeSize;
	Node* mParentNode;
	NodeType mNodeType;
};

class NodeHash
{
public:
	size_t operator() (const Node& node) const
	{
		return std::hash<int>()(node.GetNodeId());
	}
};

#endif
