#pragma once

#include <string>
#include <map>
#include <stack>
#include <iterator>

#include <iostream>
struct edge
{
	int weight;
	bool visited;
};

using NodeCoord = std::pair<int, int>;
using NodeAdj = std::map< NodeCoord, edge>;
using adjacency = std::map < NodeCoord, NodeAdj >;

//an adjacency: A:(Ax,Ay) -> (B:(Bx,By) -> w(A,B))

using NodePair = std::pair<NodeCoord, NodeCoord>;

class MazeAdj
{
public:
	MazeAdj();
	~MazeAdj();

	void addEdge(NodePair n, int w);
	void addEdge(NodeCoord A, NodeCoord B, int w);
	void addEdge(int x1, int y1, int x2, int y2, int w);

	NodeAdj getAdjacent(NodeCoord node);
	NodeAdj getAdjacent(int x, int y);

	adjacency::iterator getStart();
	adjacency::iterator getEnd();

	bool DFS(NodeCoord start, NodeCoord search);

private:
	adjacency matrix;

	std::string NodeCoordToString(NodeCoord* n);
};

