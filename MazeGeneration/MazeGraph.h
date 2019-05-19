#pragma once

#include <string>
#include <iterator>
#include <iostream>
#include <stack>
#include <map>

using NodeCoord = std::pair<int, int>;
using NodeAdj = std::map < NodeCoord, int > ;
using adjacency = std::map< NodeCoord, NodeAdj >;

//an adjacency: A:(Ax,Ay) -> (B:(Bx,By) -> w(A,B))

using NodePair = std::pair<NodeCoord, NodeCoord>;

enum direction { NORTH, EAST, SOUTH, WEST, END };

const NodeCoord nullNode = { -1, -1 };

class MazeGraph
{
public:
	const static int X_NODES = 21;
	const static int Y_NODES = 21;

	const static int boxLen = 20;
	const static int boxPad = 2;

	static NodeCoord getAdjNode(int x, int y, direction dir, int dist = 1);
	static NodeCoord getAdjNode(NodeCoord n, direction dir, int dist = 1) { return getAdjNode(n.first, n.second, dir, dist); }

	void addEdge(NodePair n, int w) { return addEdge(n.first, n.second, w); }

	void addEdge(int x1, int y1, int x2, int y2, int w) { return addEdge({ x1, y1 }, {x2, y2}, w); }

	void addEdge(NodeCoord A, NodeCoord B, int w);

	//retrieve the edge weight from the matrix
	int getEdge(NodePair p) { return getEdge(p.first, p.second); }
	int getEdge(NodeCoord A, NodeCoord B);

	//retrieve map of Nodes to weights of their edge to the paramter co-ordinates
	NodeAdj getNodeEdges(int x, int y) { return getNodeEdges({ x, y }); };
	//retrieve map of Nodes to weights of their edge to the paramter NodeCoord
	NodeAdj getNodeEdges(NodeCoord n);

private:
	adjacency matrix;
};

