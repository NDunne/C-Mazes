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
MazeNode* MazeNode::adjNode(direction d)
{
	switch (d)
	{
	case NORTH:
		if ((y - 1) > 0)
		{
			return new MazeNode(x, y - 1);
		}
	case EAST:
		if ((x + 1) < (X_NODES - 1))
		{
			return new MazeNode(x + 1, y);
		}
	case SOUTH:
		if ((y + 1) < (Y_NODES - 1))
		{
			return new MazeNode(x, y + 1);
		}
	case WEST:
		if ((x - 1) > 0)
		{
			return new MazeNode(x - 1, y);
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

