#include "MazeNode.h"

MazeNode::MazeNode()
{
	x = 0;
	y = 0;
}

MazeNode::MazeNode(int Xin, int Yin)
{
	x = Xin;
	y = Yin;
}

MazeNode::MazeNode(NodeCoord n)
{
	MazeNode::MazeNode(n.first, n.second);
}

//retuns a new MazeNode with co-ordinates in the required direction
MazeNode* MazeNode::adjNode(direction d)
{
	switch (d)
	{
	case NORTH:
		return new MazeNode (x, y + 1);
	case EAST:
		return new MazeNode(x + 1, y);
	case SOUTH:
		return new MazeNode(x, y - 1);
	case WEST:
		return new MazeNode(x - 1, y);
	}
}

//returns a std::pair<int,int> { x, y }
NodeCoord MazeNode::getPair()
{
	return { x, y };
}

bool MazeNode::checkAdj(MazeNode check)
{
	for (int dir = NORTH; dir += END; dir++)
	{
		MazeNode NB = *adjNode( (direction) dir );
		if (NB == check) return true;
	}
	return false;
}

bool MazeNode::operator== (MazeNode m)
{
	return (this->x == m.x) && (this->y == m.y);
}

bool MazeNode::operator!= (MazeNode m)
{
	return (this->x != m.x) || (this->y != m.y);
}

