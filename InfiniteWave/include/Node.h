#pragma once
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
	void SetgCost(int gCost);
	int GetgCost() const;
	void SethCost(int hCost);
	int GethCost() const;
	int GetfCost() const;
	int GetNodeId() const;
	void setNodeParent(Node* node);
	Node* GetParent() const;
	sf::Vector2i GetGridIndex() const;
	sf::Vector2f GetNodePosition(bool center = true) const;
	
	sf::RectangleShape* getDraw();
	NodeType GetType() const;
private:
	int mNodeId;
	
	sf::Vector2i mGridIndex;
	
	int m_gCost = 0;
	int m_hCost = 0;

	Node* mParentNode;
	sf::RectangleShape mNodeRect;
	NodeType mNodeType;
	sf::Vector2f mNodePostion;
	sf::Vector2f mNodeSize;
};

class NodeHash
{
public:
	size_t operator() (const Node& node) const
	{
		return std::hash<int>()(node.GetNodeId());
	}
};
