#include "MazeNode.h"

MazeNode::MazeNode()
{
	north = nullptr;
	east = nullptr;
	south = nullptr;
	west = nullptr;

	type = WALL;
}


MazeNode::~MazeNode()
{
}

MazeNode* MazeNode::getNorth()
{
	return north;
}

MazeNode* MazeNode::getEast()
{
	return east;
}

MazeNode* MazeNode::getSouth()
{
	return south;
}

MazeNode* MazeNode::getWest()
{
	return west;
}


MazeNode::NodeType MazeNode::getType()
{
	return type;
}

void MazeNode::setNorth(MazeNode* mn)
{
	north = mn;
}

void MazeNode::setEast(MazeNode* mn)
{
	east = mn;
}

void MazeNode::setSouth(MazeNode* mn)
{
	south = mn;
}

void MazeNode::setWest(MazeNode* mn)
{
	west = mn;
}

void MazeNode::setType(MazeNode::NodeType t)
{
	type = t;
}
