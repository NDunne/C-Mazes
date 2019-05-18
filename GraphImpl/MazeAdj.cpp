#include "MazeAdj.h"

void MazeAdj::addEdge(NodePair n, int w)
{
	MazeAdj::addEdge(n.first, n.second, w);
}

void MazeAdj::addEdge(int x1, int y1, int x2, int y2, int w)
{
	MazeNode* A = new MazeNode(x1, y1);
	MazeNode* B = new MazeNode(x2, y2);
	addEdge(A, B, w);
}

void MazeAdj::addEdge(MazeNode* A, MazeNode* B, int w)
{
	matrix[A->getPair()][B->getPair()] = w;
	matrix[B->getPair()][A->getPair()] = w;
}

NodeAdj MazeAdj::getNodeAdj(NodeCoord n)
{
	return matrix[n];
}

NodeAdj MazeAdj::getNodeAdj(MazeNode n)
{
	return matrix[n.getPair()];
}

NodeAdj MazeAdj::getNodeAdj(int x, int y)
{
	MazeNode* A = new MazeNode(x, y);
	return matrix[A->getPair()];
}

adjacency::iterator MazeAdj::getStart()
{
	return matrix.begin();
}

adjacency::iterator MazeAdj::getEnd()
{
	return matrix.end();
}

int MazeAdj::getEdge(MazeNode* A, MazeNode* B)
{
	return matrix[A->getPair()][B->getPair()];
}

int MazeAdj::getEdge(NodePair p)
{
	return getEdge(p.first, p.second);
}