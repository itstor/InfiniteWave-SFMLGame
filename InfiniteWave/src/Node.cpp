#include "Node.h"

#include <iostream>

Node::Node(NodeType node_type, const sf::Vector2f& node_position, const sf::Vector2f& node_size, const sf::Vector2i& grid_index, int id):mParentNode(nullptr)
{
	mNodeType = node_type;
	mNodePostion = node_position;
	mNodeSize = node_size;
	mGridIndex = grid_index;
	mNodeId = id;

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

bool Node::operator==(const Node & node) const
{
	return mNodeId == node.GetNodeId();
}

bool Node::operator!=(const Node & node) const
{
	return mNodeId != node.GetNodeId();
}

bool Node::operator<(const Node & node) const
{
	return this->GetfCost() < node.GetfCost(); //reversed, min heap
}

bool Node::operator>(const Node & node) const
{
	return this->GetfCost() > node.GetfCost();
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


//Getter setter
void Node::SetgCost(int gCost)
{
	m_gCost = gCost;
}

void Node::SethCost(int hCost)
{
	m_hCost = hCost;
}

int Node::GetgCost() const
{
	return m_gCost;
}

int Node::GethCost() const
{
	return m_hCost;
}

int Node::GetfCost() const
{
	return m_gCost + m_hCost;
}

int Node::GetNodeId() const
{
	return mNodeId;
}

void Node::setNodeParent(Node* node)
{
	mParentNode = new Node(*node);
}

Node * Node::GetParent() const
{
	return mParentNode;
}

sf::Vector2i Node::GetGridIndex() const
{
	return mGridIndex;
}

sf::Vector2f Node::GetNodePosition(bool center) const
{
	if (center)
	{
		const sf::Vector2f centerPosition(mNodePostion.x + (mNodeSize.x / 2), mNodePostion.y + (mNodeSize.y / 2));
		return centerPosition;
	}
	
	return mNodePostion;
}
