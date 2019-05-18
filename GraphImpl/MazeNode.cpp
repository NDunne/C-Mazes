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

std::string MazeNode::toString()
{
	std::string s = "(";
	s += std::to_string(x);
	s += ", ";
	s += std::to_string(y);
	s += ")";
	return s;
}

//retuns a new MazeNode with co-ordinates in the required direction
MazeNode* MazeNode::adjNode(direction dir, int dist)
{
	switch (dir)
	{
	case NORTH:
		if ((y - dist) > 0)
		{
			return new MazeNode(x, y - dist);
		}
	case EAST:
		if ((x + dist) < (X_NODES - 1))
		{
			return new MazeNode(x + dist, y);
		}
	case SOUTH:
		if ((y + dist) < (Y_NODES - 1))
		{
			return new MazeNode(x, y + dist);
		}
	case WEST:
		if ((x - dist) > 0)
		{
			return new MazeNode(x - dist, y);
		}
	}

	////LOG std::cout << "\nOut of Bounds";
	return nullptr;
}

//returns a std::pair<int,int> { x, y }
NodeCoord MazeNode::getPair()
{
	return { x, y };
}

bool MazeNode::operator== (MazeNode m)
{
	return (x == m.x) && (y == m.y);
}

bool MazeNode::operator!= (MazeNode m)
{
	return (x != m.x) || (y != m.y);
}

bool MazeNode::equals(MazeNode* m)
{
	return (x == m->x) && (y == m->y);
}
bool MazeNode::nequals(MazeNode* m)
{
	return (x != m->x) || (y != m->y);
}

