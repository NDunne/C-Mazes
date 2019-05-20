#include "MazeGraph.h"

void MazeGraph::addEdge(NodeCoord A, NodeCoord B)
{
	matrix[A][B] = 1;
	matrix[B][A] = 1;
}

void MazeGraph::removeEdge(NodeCoord A, NodeCoord B)
{
	matrix[A][B] = 0;
	matrix[B][A] = 0;
}

int MazeGraph::getEdge(NodeCoord A, NodeCoord B)
{
	return matrix[A][B];
}

NodeAdj MazeGraph::getNodeEdges(NodeCoord n)
{
	return matrix[n];
}