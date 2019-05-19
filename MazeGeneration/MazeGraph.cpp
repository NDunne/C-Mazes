#include "MazeGraph.h"

void MazeGraph::addEdge(NodeCoord A, NodeCoord B, int w)
{
	matrix[A][B] = w;
	matrix[B][A] = w;
}

int MazeGraph::getEdge(NodeCoord A, NodeCoord B)
{
	return matrix[A][B];
}

NodeAdj MazeGraph::getNodeEdges(NodeCoord n)
{
	return matrix[n];
}

NodeCoord MazeGraph::getAdjNode(int x, int y, direction dir, int dist)
{
	switch (dir)
	{
	case NORTH:
		if ((y - dist) > 0)
		{
			return { x, y - dist };
		}
		break;
	case EAST:
		if ((x + dist) < (X_NODES - 1))
		{
			return { x + dist, y };
		}
		break;
	case SOUTH:
		if ((y + dist) < (Y_NODES - 1))
		{
			return { x, y + dist };
		}
		break;
	case WEST:
		if ((x - dist) > 0)
		{
			return { x - dist, y };
		}
		break;
	}

	return nullNode;
}