#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

enum class NodeType {WALKABLE_NODE, OBSTACLE_NODE, PLAYER_NODE};

class Node
{
public:
	Node(NodeType node_type, const sf::Vector2f& node_position, const sf::Vector2f& node_size);

	sf::RectangleShape* getDraw();
	void ChangeType(NodeType node_type);
	NodeType GetType() const;
private:
	sf::RectangleShape mNodeRect;
	NodeType mNodeType;
	sf::Vector2f mNodePostion;
	sf::Vector2f mNodeSize;
};

