#include "Node.h"

Node::Node(NodeType node_type, const sf::Vector2f& node_position, const sf::Vector2f& node_size)
{
	mNodeType = node_type;
	mNodePostion = node_position;
	mNodeSize = node_size;

	//Change node outline color based on node type
	switch (mNodeType)
	{
	case NodeType::WALKABLE_NODE: mNodeRect.setOutlineColor(sf::Color::Green); break;
	case NodeType::OBSTACLE_NODE: mNodeRect.setOutlineColor(sf::Color::Red); break;
	case NodeType::PLAYER_NODE: mNodeRect.setOutlineColor(sf::Color::Blue); break;
	default: break;
	}

	mNodeRect.setSize(mNodeSize);
	mNodeRect.setPosition(mNodePostion);
	mNodeRect.setFillColor(sf::Color::Transparent);
	mNodeRect.setOutlineThickness(2.0f);
}

sf::RectangleShape * Node::getDraw()
{
	return &mNodeRect;
}

void Node::ChangeType(NodeType node_type)
{
	mNodeType = node_type;

	switch (mNodeType)
	{
	case NodeType::WALKABLE_NODE: mNodeRect.setOutlineColor(sf::Color::Green); break;
	case NodeType::OBSTACLE_NODE: mNodeRect.setOutlineColor(sf::Color::Red); break;
	case NodeType::PLAYER_NODE: mNodeRect.setOutlineColor(sf::Color::Blue); break;
	default: break;
	}
}

NodeType Node::GetType() const
{
	return mNodeType;
}